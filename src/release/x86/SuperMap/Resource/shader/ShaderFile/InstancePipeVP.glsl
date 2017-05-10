//---------------------------------------------------------------------------
//These materials/shaders are part of the NEW InstanceManager implementation
//Written by Matias N. Goldberg ("dark_sylinc")
//---------------------------------------------------------------------------
#version 120

//uv0.xy:  x分量表示顶点的纹理v坐标，y表示顶点属于线段的前后哪一个截面，0为线段的前截面，1为线段的后截面
//1,2,3三重纹理坐标表示前截面的模型矩阵，4,5,6三重纹理坐标表示后截面的模型矩阵，
//uv7.xy:  x分量为后截面的u方向纹理坐标，y分量为前截面的u方向纹理坐标

//Parameters
uniform mat4 texture0_matrix;
uniform mat4 worldview_matrix;
uniform vec3 light_position;
uniform vec4 light_diffuse_colour;
uniform vec3 camera_position;
uniform mat4 matInv;
uniform vec3 localCenter;
uniform vec4 viewport_size;
#if PIPEDATASET
uniform float pipeWidth;
#endif

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;
attribute vec4 uv6;
attribute vec4 uv7;

varying vec4 clip_vertex;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void DirectionalLight(in vec3 ecPosition, in vec3 vNormal, inout vec4 diffuse, inout vec4 specular, inout float highLight)
{
	// 管线使用固定光源，在局部坐标系中从上斜向下发射
	vec3 vp = vec3(0.0, 0.4472136, 0.894427);
	float nDotVP = max(0.0, dot(vNormal, vp));
	diffuse += light_diffuse_colour * nDotVP;

	// 计算从表面点到摄像机的向量
	vec3 localCameraPos = camera_position - localCenter;
	vec3 eye = normalize(ecPosition - localCameraPos);

	// 计算视线与光线的半向量
	vec3 halfVector = normalize(vp+eye);
	float nDotHV = dot(vNormal, halfVector);
	// 粗糙度，越小越光滑
	float shininess = 20.0;
	// 镜面反射光强度因子
	float powerFactor = max(0.0, pow(nDotHV, shininess));
	specular += vec4(powerFactor);

	// 计算高光系数
	highLight = 0.5 * (1.0 + dot(vp, vNormal));
	highLight = clamp(highLight, 0.8, 1.0);
}

void main(void)
{
	vec4 worldPos;
	vec4 worldPos0;
	vec4 worldPos1;

	mat4 worldMatrix;
	mat4 worldMatrix0;
	mat4 worldMatrix1;

	worldMatrix0[0] = uv1;
	worldMatrix0[1] = uv2;
	worldMatrix0[2] = uv3;
	worldMatrix0[3] = vec4( 0, 0, 0, 1.0);

	worldMatrix1[0] = uv4;
	worldMatrix1[1] = uv5;
	worldMatrix1[2] = uv6;
	worldMatrix1[3] = vec4( 0, 0, 0, 1.0);

	vec4 realVertex = vec4(vertex.xyz, 1.0);
	realVertex.x = realVertex.x * uv7.z;

	worldPos0 = realVertex * worldMatrix0;
	worldPos1 = realVertex * worldMatrix1;

	if(uv0.y > 0.5)
	{
		gl_TexCoord[0] = texture0_matrix * vec4(uv7.y, uv0.x, 0.0, 1.0);
		worldPos = worldPos1;
		worldMatrix = worldMatrix1;
	}
	else
	{
		gl_TexCoord[0] = texture0_matrix * vec4(uv7.x, uv0.x, 0.0, 1.0);
		worldPos = worldPos0;
		worldMatrix = worldMatrix0;
	}

	vec4 viewPos = gl_ModelViewMatrix * worldPos;
	gl_ClipVertex = viewPos;
	clip_vertex = gl_ClipVertex;

#if PIPEDATASET
	vec4 midWorldPos = (worldPos0 + worldPos1) * 0.5;
	midWorldPos.w = 1.0;
	vec4 midViewPos = gl_ModelViewMatrix * midWorldPos;

	//计算管线占的屏幕像素，采用UGC中ComputerLength2Pix的方法，相机张角按45度算
	float pixelCount = viewport_size.y * pipeWidth * 1.207 / length(midViewPos);
	if(pixelCount > 3.0)
	{
		//Transform the position
		gl_Position = gl_ModelViewProjectionMatrix * worldPos;

		vec3 realNormal = normal;
		realNormal.x = normal.x * uv7.z;
		vec3 worldNorm = normalize(realNormal * mat3(worldMatrix));

		// 计算定向光各通道强度
		vec4 diffuseTemp = vec4(0.0);
		vec4 specularTemp = vec4(0.0);
		// 高光系数，用于增加对比度
		float highLight = 1.0;

		DirectionalLight(worldPos.xyz, worldNorm, diffuseTemp, specularTemp, highLight);
		gl_FrontColor = (gl_LightModel.ambient + diffuseTemp * vec4(0.75) + specularTemp) * colour;
		gl_FrontColor.rgb = highLight * gl_FrontColor.rgb;
	}
	else //小于3个屏幕像素，就按照固定的3个屏幕像素渲染
	{
		// 计算线段的屏幕坐标
		gl_Position = gl_ModelViewProjectionMatrix * worldPos;
		gl_Position.xy += vec2(4.242) * uv0.x * viewport_size.z * gl_Position.w;
		gl_FrontColor = colour;
	}
#else
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;

	vec3 realNormal = normal;
	realNormal.x = normal.x * uv7.z;
	vec3 worldNorm = normalize(realNormal * mat3(worldMatrix));

	// 计算定向光各通道强度
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);
	// 高光系数，用于增加对比度
	float highLight = 1.0;

	DirectionalLight(worldPos.xyz, worldNorm, diffuseTemp, specularTemp, highLight);
	gl_FrontColor = (gl_LightModel.ambient + diffuseTemp * vec4(0.75) + specularTemp) * colour;
	gl_FrontColor.rgb = highLight * gl_FrontColor.rgb;
#endif

#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
