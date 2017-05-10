attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;
attribute vec4 uv6;
attribute vec4 uv7;

//Parameters
uniform mat4 texture0_matrix;

varying vec4 mixColor;
varying vec4 texcoordDepth;
varying vec4 clip_vertex;

void main()
{
	mat4 worldMatrix;
	vec4 realVertex = vec4(vertex.xyz, 1.0);
	if(uv0.y > 0.5)
	{
		worldMatrix[0] = uv4;
		worldMatrix[1] = uv5;
		worldMatrix[2] = uv6;
		// 计算纹理坐标
		texcoordDepth.xy = vec2(texture0_matrix * vec4(uv7.y, uv0.x, 0.0, 1.0));
	}
	else
	{
		worldMatrix[0] = uv1;
		worldMatrix[1] = uv2;
		worldMatrix[2] = uv3;
		// 计算纹理坐标
		texcoordDepth.xy = vec2(texture0_matrix * vec4(uv7.x, uv0.x, 0.0, 1.0));
	}
	worldMatrix[3] = vec4( 0, 0, 0, 1 );

	realVertex.x = realVertex.x * uv7.z;

	vec4 worldPos		= realVertex * worldMatrix;
	//Transform the position
	gl_Position = gl_ModelViewProjectionMatrix * worldPos;
	gl_ClipVertex = gl_ModelViewMatrix * worldPos;
	clip_vertex = gl_ClipVertex;
	texcoordDepth.zw = gl_Position.zw;

	mixColor = colour;
}
