#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

// ��������
uniform sampler2D texture0; //�ֲڲ�
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

// ��������߽�
uniform vec4 texture0Bound;
uniform vec4 texture1Bound;
uniform vec4 texture2Bound;
uniform vec4 texture3Bound;

uniform float transparent;	// �ر�͸��ֵ

varying vec4 globalBound;	// ȫ������߽�
varying vec2 texCoord;
varying vec3 realNormal;
varying vec3 vLight;
varying vec3 vec3Rayleigh;
varying vec3 vec3AdjustedMie;
varying float fFogFactor;
varying vec3 vertNorm;

varying vec4 mixColor;

const vec3 fogColor = vec3(1.0);

// �жϵ��Ƿ��ھ�����
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}

bool isPointInRegionExt(vec2 point, vec4 region)
{
	if (region.x > region.z)
	{
		// ��Խȫ��߽�����
		vec4 region0 = vec4(region.x, region.y, globalBound.z, region.w);
		vec4 region1 = vec4(globalBound.x, region.y, region.z, region.w);

		if (isPointInRegion(point, region0) || isPointInRegion(point, region1))
		{
			return true;
		}
	}
	else if (isPointInRegion(point, region))
	{
		return true;
	}

	return false;
}

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	vec4 color = vec4(0.0);
	
	
	// ���� bound ȡ����
	if (isPointInRegionExt(texCoord, texture3Bound))
	{
		color = texture2D(texture3, gl_TexCoord[3].xy);
	}
	else if (isPointInRegionExt(texCoord, texture2Bound))
	{
		color = texture2D(texture2, gl_TexCoord[2].xy);
	}
	else if (isPointInRegionExt(texCoord, texture1Bound))
	{
		color = texture2D(texture1, gl_TexCoord[1].xy);
	}
	else
	{
		color = texture2D(texture0, gl_TexCoord[0].xy);
	}
	color = color * mixColor;

	vec3 postionToLight = vLight;

	//�Ե�ǰλ�ý����ֲ�����ϵ���Ե�ǰ�ر�λ�õ�ԭʼ���߷���Ϊz��
	vec3 zAxis = normalize(vertNorm);
	//��þֲ�����ϵy��
	vec3 xAxis = normalize(vec3(-vertNorm.y, vertNorm.x, 0));
	vec3 yAxis = normalize(cross(zAxis, xAxis));
	mat3 matrix = mat3(xAxis, yAxis, zAxis);
	//������η��ߵ���������
	vec3 vNormal = matrix * realNormal;
	vNormal = normalize(vNormal);
	//̫����Ϊֱ����Դ��ɢ��ϵ��	
	float diffuse = max(dot(postionToLight, vNormal), 0.125);
	//��ֱ���Դ�ʹ���mieɢ������Ϊɢ��ϵ��
	vec3 realDiffuse = mix(vec3AdjustedMie, vec3(diffuse), 0.35);
	vec3 scatteredColor = vec3Rayleigh + color.rgb * realDiffuse;
	color.rgb = mix(fogColor, scatteredColor, fFogFactor);
	//color.rgb = vec3(1.0) - exp(color.rgb * -2);
	color.a = transparent;
	gl_FragColor = color;
}