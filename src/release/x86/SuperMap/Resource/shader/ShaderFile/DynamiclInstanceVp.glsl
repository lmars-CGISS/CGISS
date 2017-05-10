#include <lib/Quaternion4d.glsllib>

uniform float fTimeValue;
uniform float fTimeSinceBegin;
uniform vec3 vEyePosHigh;
uniform vec3 vEyePosLow;

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 colour;		 // 存储变化前后的颜色
attribute vec4 uv0;			 // 纹理坐标

attribute vec3 blendWeights; // xyz轴缩放比例1
attribute vec3 blendIndices; // xyz轴缩放比例2

attribute vec4 uv1;			 // 位置12的X位 按照High1 Low1 High2 Low2排列
attribute vec4 uv2;			 // 位置12的Y位 按照High1 Low1 High2 Low2排列
attribute vec4 uv3;			 // 位置12的Z位 按照High1 Low1 High2 Low2排列
attribute vec4 uv4;			 // xyz为自转轴 w为自转角速度
attribute vec4 uv5;			 // 矩阵第一行
attribute vec4 uv6;			 // 矩阵第二行
attribute vec4 uv7;			 // 矩阵第三行

varying vec4 clip_vertex;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void DirectionalLight(in vec3 ecPosition, in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	// 计算从表面点到摄像机的向量
	//vec3 eye = vec3(normalize(cameraPos-ecPosition));
	vec3 eye = -normalize(ecPosition);
	vec3 vp = normalize(vec3(gl_LightSource[0].position));
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

void unpackColor(in vec4 color, out vec4 color1, out vec4 color2)
{
	color1 = vec4(1.0);
	color2 = vec4(1.0);

	color1.r = floor(color.r) * 0.001;
	color1.g = fract(color.r) * 10.0;
	color1.b = floor(color.g) * 0.001;
	color1.a = fract(color.g) * 10.0;

	color2.r = floor(color.b) * 0.001;
	color2.g = fract(color.b) * 10.0;
	color2.b = floor(color.a) * 0.001;
	color2.a = fract(color.a) * 10.0;
}

vec3 computeRelEyePos(vec3 posHigh, vec3 posLow)
{
	vec3 t1 = posLow - vEyePosLow;
	vec3 e = t1 - posLow;
	vec3 t2 = ((-vEyePosLow - e) + (posLow - (t1 - e))) + posHigh - vEyePosHigh;
	vec3 highDifference = t1 + t2;
	vec3 lowDifference = t2 - (highDifference - t1);
	return (highDifference + lowDifference);
}

void main(void)
{
	vec3 pos1High = vec3(uv1.x, uv2.x, uv3.x);
	vec3 pos2High = vec3(uv1.z, uv2.z, uv3.z);
	vec3 pos1Low = vec3(uv1.y, uv2.y, uv3.y);
	vec3 pos2Low = vec3(uv1.w, uv2.w, uv3.w);
	vec3 relEyePos1 = computeRelEyePos(pos1High, pos1Low);
	vec3 relEyePos2 = computeRelEyePos(pos2High, pos2Low);
	vec3 mixTrans = mix(relEyePos1, relEyePos2, fTimeValue);

	vec3 rotAxis = normalize(uv4.xyz);
	float fCurrentAnalge = fTimeSinceBegin * uv4.w;
	vec4 quaCurrent = FromAngleAxis(fCurrentAnalge, rotAxis);
	mat4 rot = QuaToRotationMatrix(quaCurrent);

	mat4 worldMatrix;
	worldMatrix[0] = uv5;
	worldMatrix[1] = uv6;
	worldMatrix[2] = uv7;
	worldMatrix[3] = vec4( 0.0, 0.0, 0.0, 1.0);

	worldMatrix[0][3] = mixTrans.x;
	worldMatrix[1][3] = mixTrans.y;
	worldMatrix[2][3] = mixTrans.z;

	vec3 mixScale = mix(blendWeights, blendIndices, fTimeValue);
	mat4 scaleMatrix;
	scaleMatrix[0] = vec4( mixScale.x, 0.0, 0.0, 0.0);
	scaleMatrix[1] = vec4( 0.0, mixScale.y, 0.0, 0.0);
	scaleMatrix[2] = vec4( 0.0, 0.0, mixScale.z, 0.0);
	scaleMatrix[3] = vec4( 0.0, 0.0, 0.0, 1.0);

	worldMatrix = rot * scaleMatrix * worldMatrix;

	gl_TexCoord[0] = gl_TextureMatrix[0] * uv0;
	
	vec4 worldPos = vec4(vertex.xyz, 1.0) * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

	// 计算定向光各通道强度
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);
	
	vec3 newNormal = normal * mat3(worldMatrix);
	newNormal = vec3(gl_NormalMatrix * newNormal);
	newNormal = normalize(newNormal);
	newNormal = newNormal * gl_NormalScale;

	vec4 clip_vertex = gl_ModelViewMatrix * worldPos;
	DirectionalLight(clip_vertex.xyz, newNormal, ambientTemp, diffuseTemp, specularTemp);
	
	vec4 mixColor = gl_FrontLightModelProduct.sceneColor
		+ ambientTemp*gl_FrontMaterial.ambient
		+ diffuseTemp*gl_FrontMaterial.diffuse
		+ specularTemp*gl_FrontMaterial.specular;
	mixColor.a = gl_FrontMaterial.diffuse.a;
	mixColor = clamp(mixColor, vec4(0.0), vec4(1.0));

	vec4 color1 = vec4(1.0);
	vec4 color2 = vec4(1.0);
	unpackColor(colour, color1, color2);
	vec4 mixVertexColor = mix(color1, color2, fTimeValue);
	gl_FrontColor = mixColor * mixVertexColor;
}
