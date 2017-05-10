//---------------------------------------------------------------------------
//These materials/shaders are part of the NEW InstanceManager implementation
//Written by Matias N. Goldberg ("dark_sylinc")
//---------------------------------------------------------------------------
//#version 120
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;

//Parameters
uniform mat4 texture0_matrix;

varying vec4 mixColor;
varying vec4 texcoordDepth;
varying vec4 clip_vertex;

void main(void)
{
	mat4 worldMatrix;
	worldMatrix[0] = uv2;
	worldMatrix[1] = uv3;
	worldMatrix[2] = uv4;
	worldMatrix[3] = vec4( 0, 0, 0, 1 );

	texcoordDepth = texture0_matrix * uv1;
	
	vec4 worldPos		= vec4(gl_Vertex.xyz, 1.0) * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	gl_ClipVertex = gl_ModelViewMatrix * worldPos;
	clip_vertex = gl_ClipVertex;

	texcoordDepth.zw = gl_Position.zw;
	mixColor = gl_Color;
}
