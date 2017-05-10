//---------------------------------------------------------------------------
//These materials/shaders are part of the NEW InstanceManager implementation
//Written by Matias N. Goldberg ("dark_sylinc")
//---------------------------------------------------------------------------
//#version 120

//Parameters
uniform sampler2D selectionTexture;
uniform vec3 light_position;

varying vec4 vec4SelectionColor;  // 选中颜色
varying vec4 clip_vertex;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;
attribute vec3 normal;
attribute vec4 secondary_colour;

void DirectionalLight(in vec3 ecPosition, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	// 计算从表面点到摄像机的向量
	//vec3 eye = vec3(normalize(cameraPos-ecPosition));
	vec3 eye = -normalize(ecPosition);
	vec3 vp = normalize(vec3(light_position));
	// 计算视线与光线的半向量
	vec3 halfVector = normalize(vp+eye);
	
	float nDotVP = max(0.0, dot(normal, vp));
	float nDotHV = dot(normal, halfVector);

	// 粗糙度，越小越光滑
	float shininess = 50.0;//gl_FrontMaterial.shininess;
	// 镜面反射光强度因子
	float powerFactor = max(0.0, pow(nDotHV, shininess));

	ambient += gl_LightSource[0].ambient;
	diffuse += gl_LightSource[0].diffuse * nDotVP;
	specular += gl_LightSource[0].specular * powerFactor;
}

void main(void)
{
	mat4 worldMatrix;
	worldMatrix[0] = uv2;
	worldMatrix[1] = uv3;
	worldMatrix[2] = uv4;
	worldMatrix[3] = vec4( 0, 0, 0, 1 );

	gl_TexCoord[0] = gl_TextureMatrix[0] * uv0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * uv1;
	
	vec4 worldPos		= vec4(gl_Vertex.xyz, 1.0) * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	gl_ClipVertex = gl_ModelViewMatrix * worldPos;
	clip_vertex = gl_ClipVertex;
	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

	// 计算定向光各通道强度
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);
	
	vec3 newNormal = normalize(normal * mat3(worldMatrix));
 
	DirectionalLight(clip_vertex.xyz, newNormal, ambientTemp, diffuseTemp, specularTemp);
	vec4 mixColor = gl_FrontLightModelProduct.sceneColor
		+ ambientTemp*gl_FrontMaterial.ambient
		+ diffuseTemp*gl_FrontMaterial.diffuse
		+ specularTemp*gl_FrontMaterial.specular;
	mixColor.a = gl_FrontMaterial.diffuse.a;
	mixColor = clamp(mixColor, vec4(0.0), vec4(1.0));

	gl_FrontColor = mixColor;

	//处理选择颜色
	vec4SelectionColor = vec4(1.0, 1.0, 1.0, 1.0);
	if(secondary_colour.r < 0.99 || secondary_colour.g < 0.99 || secondary_colour.b < 0.99 || secondary_colour.a < 0.99)
	{
		vec4 selColor = texture2D(selectionTexture, vec2(0.5, 0.5));
		float r = abs(secondary_colour.r - selColor.r);
		float g = abs(secondary_colour.g - selColor.g);
		float b = abs(secondary_colour.b - selColor.b);
		float a = abs(secondary_colour.a - selColor.a);

		if(r < 0.003 && g < 0.003 && b < 0.003 && a < 0.003)
		{
			vec4SelectionColor = vec4(0.7,0.6,0.8,1.0);
		}
	}
	
	vec4SelectionColor = vec4SelectionColor * gl_Color;
	vec4SelectionColor = vec4SelectionColor * uv5;
}
