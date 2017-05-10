//---------------------------------------------------------------------------
//These materials/shaders are part of the NEW InstanceManager implementation
//Written by Matias N. Goldberg ("dark_sylinc")
//---------------------------------------------------------------------------
//#version 120

//Parameters
uniform sampler2D selectionTexture;

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;
attribute vec4 secondary_colour;

varying vec4 clip_vertex;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void DirectionalLight(in vec3 ecPosition, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	// ����ӱ���㵽�����������
	//vec3 eye = vec3(normalize(cameraPos-ecPosition));
	vec3 eye = -normalize(ecPosition);
	vec3 vp = normalize(vec3(gl_LightSource[0].position));
	// ������������ߵİ�����
	vec3 halfVector = normalize(vp+eye);
	
	float nDotVP = max(0.0, dot(normal, vp));
	float nDotHV = dot(normal, halfVector);

	// �ֲڶȣ�ԽСԽ�⻬
	float shininess = 50.0;//gl_FrontMaterial.shininess;
	// ���淴���ǿ������
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
	
	vec4 worldPos		= vec4(vertex.xyz, 1.0) * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	gl_ClipVertex = gl_ModelViewMatrix * worldPos;
	clip_vertex = gl_ClipVertex;
	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

	// ���㶨����ͨ��ǿ��
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);
	
	mat3 worldMatrix3;
	worldMatrix3[0] = worldMatrix[0].xyz;
	worldMatrix3[1] = worldMatrix[1].xyz;
	worldMatrix3[2] = worldMatrix[2].xyz;
	vec3 newNormal = normal * worldMatrix3;
	newNormal = vec3(gl_NormalMatrix * newNormal);
	newNormal = normalize(newNormal);
	newNormal = newNormal * gl_NormalScale;

	DirectionalLight(clip_vertex.xyz, newNormal, ambientTemp, diffuseTemp, specularTemp);
	
	vec4 mixColor = gl_FrontLightModelProduct.sceneColor
		+ ambientTemp*gl_FrontMaterial.ambient
		+ diffuseTemp*gl_FrontMaterial.diffuse
		+ specularTemp*gl_FrontMaterial.specular;
	mixColor.a = gl_FrontMaterial.diffuse.a;
	mixColor = clamp(mixColor, vec4(0.0), vec4(1.0));

	gl_FrontColor = mixColor * uv5 * gl_Color;
}
