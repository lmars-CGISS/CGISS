//---------------------------------------------------------------------------
//These materials/shaders are part of the NEW InstanceManager implementation
//Written by Matias N. Goldberg ("dark_sylinc")
//---------------------------------------------------------------------------
#version 120

//uv0.xy:  x分量表示顶点的纹理v坐标，y表示顶点属于线段的前后哪一个截面，0为线段的前截面，1为线段的后截面
//1,2,3三重纹理坐标表示前截面的模型矩阵，4,5,6三重纹理坐标表示后截面的模型矩阵，
//uv7.xy:  x分量为后截面的u方向纹理坐标，y分量为前截面的u方向纹理坐标

attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 secondary_colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;
attribute vec4 uv6;
attribute vec4 uv7;

varying vec4 vecVertexColor;
varying vec4 clip_vertex;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void main(void)
{
	mat4 worldMatrix;
	vec4 realVertex = vec4(vertex.xyz, 1.0);
	if(uv0.y > 0.5)
	{
		worldMatrix[0] = uv4;
		worldMatrix[1] = uv5;
		worldMatrix[2] = uv6;
	}
	else
	{
		worldMatrix[0] = uv1;
		worldMatrix[1] = uv2;
		worldMatrix[2] = uv3;
	}
	worldMatrix[3] = vec4( 0, 0, 0, 1 );

	realVertex.x = realVertex.x * uv7.z;

	vec4 worldPos		= realVertex * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	gl_ClipVertex = gl_ModelViewMatrix * worldPos;
	clip_vertex = gl_ClipVertex;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

	vecVertexColor = vec4(0.0, 0.0, 0.0, 0.0);
	if(colour.a > 0.0)
	{
		vecVertexColor = secondary_colour;
	}
}
