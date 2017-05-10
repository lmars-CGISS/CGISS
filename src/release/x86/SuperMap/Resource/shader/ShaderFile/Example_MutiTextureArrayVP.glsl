#version 120

varying vec3 oUv[8];
varying vec2 index;

uniform mat4 worldViewProj;
uniform mat4 textureMatrix0;
uniform mat4 textureMatrix1;
uniform mat4 textureMatrix2;
uniform mat4 textureMatrix3;
uniform mat4 textureMatrix4;
uniform mat4 textureMatrix5;
uniform mat4 textureMatrix6;
uniform mat4 textureMatrix7;

uniform vec4 lightPosition;
uniform vec3 lightDiffuse;

void DirectionalLight(in vec3 ecPosition3, in vec3 normal
	, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	float nDotVP;			// normal . light direction
	float nDotHV;			// normal . light half vector
	float pf;				// ÃÝµÄÒò×Ó
	
	nDotVP = max(0.0, dot(normal, vec3(gl_LightSource[0].position)));
	nDotHV = max(0.0, dot(normal, vec3(gl_LightSource[0].halfVector)));

	if(nDotVP == 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, gl_FrontMaterial.shininess);

	ambient += gl_LightSource[0].ambient;
	diffuse += gl_LightSource[0].diffuse * nDotVP;
	specular += gl_LightSource[0].specular * pf;
}

void main(void)
{
	vec4 ecPosition = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	vec3 ecPosition3 = ecPosition.xyz / ecPosition.w;

	vec4 amb = vec4(0.0);
	vec4 diff = vec4(0.0);
	vec4 spec = vec4(0.0);

	vec3 normal = gl_NormalMatrix * gl_Normal;
	normal = normalize(normal);
	normal = normal * gl_NormalScale;
	
	DirectionalLight(ecPosition3, normal, amb, diff, spec);
	
	vec4 color = gl_FrontLightModelProduct.sceneColor
		+ amb * gl_FrontMaterial.ambient
		+ diff * gl_FrontMaterial.diffuse;
	color += spec * gl_FrontMaterial.specular;

	gl_FrontColor = clamp(color, 0.0, 1.0);
	
	gl_Position = worldViewProj * vec4(gl_Vertex.xyz, 1.0);
	
	oUv[0] = vec3(textureMatrix0 * gl_MultiTexCoord0);
	oUv[1] = vec3(textureMatrix1 * gl_MultiTexCoord1);
	oUv[2] = vec3(textureMatrix2 * gl_MultiTexCoord0);
	oUv[3] = vec3(textureMatrix3 * gl_MultiTexCoord1);
	
	oUv[4] = vec3(textureMatrix4 * gl_MultiTexCoord0);
	oUv[5] = vec3(textureMatrix5 * gl_MultiTexCoord1);
	oUv[6] = vec3(textureMatrix6 * gl_MultiTexCoord0);
	oUv[7] = vec3(textureMatrix7 * gl_MultiTexCoord1);
	
	index.x = gl_MultiTexCoord0.z;
}
