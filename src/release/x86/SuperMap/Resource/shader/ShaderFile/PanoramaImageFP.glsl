#if GL_ES
	precision mediump float;
#endif

uniform mat4 inverse_view_projection_matrix;
uniform mat4 inverse_world_view_projection_matrix;

uniform mat4 worldview_matrix;
uniform mat4 inverse_projection_matrix;
uniform vec3 light_direction_view_space;
uniform vec4 ambient_light_colour;
uniform vec4 light_diffuse_colour;
uniform vec4 light_specular_colour;

uniform vec4 surface_ambient_colour;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;

//������
#if TEX2D
	uniform sampler2D texture0;
#else
	uniform sampler3D texture0;
#endif

//�������
uniform sampler2D texture1;

//��ɫ������
uniform sampler2D texture2;

uniform mat4 texture0_matrix;

varying vec4 texCoord;
varying vec4 clip_pos;
varying float fWindowZ;

//���ݷ�Χ
uniform vec3 vMin;
uniform vec3 vMax;

//��ɫ�������Сֵ
uniform float floor;
uniform float ceil;
//�����С�ɼ�ֵ
uniform float maxVisibleValue;
uniform float minVisibleValue;

//�Ƿ�ʹ����ɫ��
uniform int bHasColorTable;

//�ȸ��߼�ļ��
uniform float contourInterval;
//�ȸ��ߵ���ɫ
uniform vec4 lineColor;

//�ȸ��ߵ����ģʽ   0-ʲô������ 1-ֻ�����ɫ  
//2-ֻ���Ƶȸ���  3-���Ƶȸ��߲������ɫ
uniform int contourFillMode;
//͸����
uniform float opacity;

//  1/2048
const float fOffset = 0.00048828125; 

void writeDepthClampedToFarPlane()
{
    gl_FragDepth = min(fWindowZ * gl_FragCoord.w, 1.0);
}

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	depth = depth * 2.0 - 1.0;
	return clamp(depth,-1.0,1.0);
}

float getDepth( in vec2 uv, in vec2 pixelOffset )
{
	vec2 depthTexCoord = uv + pixelOffset * fOffset;
	
#if FLOAT_TEXTURE
	float depthValue = texture2D(texture1, depthTexCoord.xy).x;
#else
	vec4 depthRGBA = texture2D(texture1, depthTexCoord.xy).rgba;
	float depthValue = unpackDepth(depthRGBA);
#endif

	return depthValue;
}

vec3 getPos( in vec2 uv, in vec2 pixelOffset )
{
	float depthValue = getDepth( uv, pixelOffset );
	vec4 pos = clip_pos/clip_pos.w;
	pos.z = depthValue;
	pos.x = pos.x + pixelOffset.x * fOffset * 2.0;
	pos.y = pos.y - pixelOffset.y * fOffset * 2.0;
	pos = inverse_projection_matrix*pos;
	pos = pos/pos.w;
	return pos.xyz;
}


void directionalLight(in vec3 ecPosition, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	// ����ӱ���㵽�����������
	vec3 eye = -normalize(ecPosition);
	vec3 vp = vec3(1.0, 0.0, 0.0);
	// ������������ߵİ�����
	vec3 halfVector = normalize(vp+eye);
	
	float nDotVP = max(0.0, dot(normal, vp));
	float nDotHV = max(0.0, dot(normal, halfVector));

	// �ֲڶȣ�ԽСԽ�⻬
	float shininess = 50.0;//gl_FrontMaterial.shininess;
	// ���淴���ǿ������
	float powerFactor = max(0.0, pow(nDotHV, shininess));

	ambient += ambient_light_colour;
	diffuse += light_diffuse_colour * nDotVP;
	specular += light_specular_colour * powerFactor;
}


float computeMixCon(in float value)
{
	//�ȸ��ߺ͵Ǹ߷ֲ���ɫ
	float distanceToContour = mod(value-0.0002, contourInterval);
	float dxc = abs(dFdx(value));
	float dyc = abs(dFdy(value));
	float dF = max(dxc, dyc);
	return (distanceToContour < dF)?1.0:0.0;
}

vec4 getFillColor(in float value)
{
	if (value < minVisibleValue || value > maxVisibleValue)
	{
		discard;
	}

	float threshold = clamp(abs(ceil-floor),0.000001,20000.0);
	float contourRate = (value-floor)/threshold;
	float finalCoord = clamp(contourRate,0.0,1.0);
	return texture2D(texture2, vec2(0.0, finalCoord)).rgba;
}

//��������RGBAͨ���е��ĸ�byte��ԭΪfloat
float Convert4ByteToFloat(vec4 vByte)
{
	//b,g,r,aͨ���ֱ𱣴���ԭʼ�߶ȵ��ĸ�byte�������Ҫ�������λ�ƻ�ԭ��ԭ����λ��aͨ���洢�߶�ֵ�Ƿ�Ϊ��ֵ��1Ϊ��ֵ��0Ϊ��ֵ
	//�߶���CPU��������һǧ������˳�0.001��byte�Զ����ŵ�0.0-1.0֮�䣬��˳�255
	if(vByte.a > 0.5)
	{
		return -(vByte.b + vByte.g * 256.0 + vByte.r * 65536.0) * 0.255;
	}
	else
	{
		return (vByte.b + vByte.g * 256.0 + vByte.r * 65536.0) * 0.255;
	}
	
}

void main()
{
	vec4 depthTexCoord = clip_pos / clip_pos.w;
	depthTexCoord.xy = depthTexCoord.xy * 0.5 + 0.5;
	depthTexCoord.y = 1.0 - depthTexCoord.y;
	
	float depthValue = getDepth(depthTexCoord.xy, vec2(0.0,0.0));

	vec4 pos = clip_pos;

	pos.z = depthValue * pos.w;
	vec4 imageViewPos = inverse_world_view_projection_matrix * pos;
	imageViewPos = imageViewPos / imageViewPos.w;



	if(imageViewPos.x < vMin.x || imageViewPos.y < vMin.y || imageViewPos.z < vMin.z 
	|| imageViewPos.x > vMax.x || imageViewPos.y > vMax.y || imageViewPos.z > vMax.z)
	{
		discard;
	}

	
	vec3 vPos0 = getPos(depthTexCoord.xy, vec2(0.0,0.0));
	vec3 vPos1 = getPos(depthTexCoord.xy, vec2(1.0,0.0));//�ұߵĵ�
	vec3 vPos2 = getPos(depthTexCoord.xy, vec2(0.0,-1.0));//�ϱߵĵ�
	vec3 vPos3 = getPos(depthTexCoord.xy, vec2(-1.0,0.0));//�ұߵĵ�
	vec3 vPos4 = getPos(depthTexCoord.xy, vec2(0.0,1.0));//�ϱߵĵ�

	vec3 cross0;
	cross0 = normalize( cross( (vPos1 - vPos0), (vPos2 - vPos0)) );

	vec3 cross1;
	cross1 = normalize( cross( (vPos0 - vPos3), (vPos0 - vPos4)) );

	vec3 normal = normalize(cross0 + cross1/* + cross2 + cross3*/);

	
	// ���㶨����ͨ��ǿ��
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);

	directionalLight(vPos0, normal, ambientTemp, diffuseTemp, specularTemp);

	vec4 mixColor = ambientTemp*surface_ambient_colour
		+ diffuseTemp*surface_diffuse_colour
		+ specularTemp*surface_specular_colour;

	vec4 texCoord;
	texCoord.x = (imageViewPos.x - vMin.x)/(vMax.x - vMin.x);
	texCoord.y = (imageViewPos.y - vMin.y)/(vMax.y - vMin.y);
	texCoord.z = (imageViewPos.z - vMin.z)/(vMax.z - vMin.z);
	texCoord.w = 1.0;

	texCoord = texture0_matrix * texCoord;

	vec4 color;

	if(bHasColorTable > 0)
	{
		float value = 0.0;
#if TEX2D

#if FLOAT_TEXTURE
		value = texture2D(texture0, texCoord.xy).x;
#else
		vec4 vec4value = texture2D(texture0, texCoord.xy).xyzw;
		value = Convert4ByteToFloat(vec4value);
#endif

#else

#if FLOAT_TEXTURE
		value = texture3D(texture0, texCoord.xyz).x;
#else
		vec4 vec4value = texture3D(texture0, texCoord.xyz).xyzw;
		value = Convert4ByteToFloat(vec4value);
#endif

#endif

		if(contourFillMode == 1)
		{//����ɫ
			color = getFillColor(value);
		}
		else if(contourFillMode == 2)
		{//����
			if(computeMixCon(value) > 0.5)
			{
				color = lineColor;
			}
			else
			{
				discard;
			}
		}
		else if(contourFillMode == 3)
		{//����
			vec4 fillColor = getFillColor(value);
			float mix_con = computeMixCon(value);
			color = mix(fillColor, lineColor, mix_con);
		}
		else
		{//������
			discard;
		}
	}
	else
	{
#if TEX2D
		color = texture2D(texture0, texCoord.xy);
#else
		color = texture3D(texture0, texCoord.xyz);
#endif
	}


	gl_FragColor = color * mixColor;

	gl_FragColor.a = opacity;

	writeDepthClampedToFarPlane();
}