//---------------------------------------------------------------------------
//These materials/shaders are part of the NEW InstanceManager implementation
//Written by Matias N. Goldberg ("dark_sylinc")
//---------------------------------------------------------------------------
#version 120

//uv0.xy:  x������ʾ���������v���꣬y��ʾ���������߶ε�ǰ����һ�����棬0Ϊ�߶ε�ǰ���棬1Ϊ�߶εĺ����
//1,2,3�������������ʾǰ�����ģ�;���4,5,6�������������ʾ������ģ�;���
//uv7.xy:  x����Ϊ������u�����������꣬y����Ϊǰ�����u������������

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
