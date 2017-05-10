attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;

//Parameters
uniform mat4 texture0_matrix;
uniform mat4 worldview_matrix;
uniform mat4 matInv;

varying vec4 mixColor;
varying vec4 texcoordDepth;
varying vec4 clip_vertex;

void main()
{
	mat4 worldMatrix;
	worldMatrix[0] = uv2;
	worldMatrix[1] = uv3;
	worldMatrix[2] = uv4;
	worldMatrix[3] = vec4( 0, 0, 0, 1 );

	texcoordDepth = gl_TextureMatrix[0] * uv0;
	
	vec4 worldPos		= vec4(vertex.xyz, 1.0) * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	gl_ClipVertex = gl_ModelViewMatrix * worldPos;
	clip_vertex = gl_ClipVertex;

	texcoordDepth.zw = gl_Position.zw;

	mixColor = colour;
}
