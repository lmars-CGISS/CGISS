attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;
uniform mat4 texture0_matrix;
#if !GL_ES
uniform mat4 worldview_matrix;
#endif

varying vec4 mixColor;
varying vec4 texcoordDepth;
varying vec4 clip_vertex;

void main()
{
	mixColor = colour;
	texcoordDepth.xy = vec2(texture0_matrix * uv0);

	// 投影到屏幕上的位置
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
#if !GL_ES
	gl_ClipVertex = worldview_matrix * vec4(vertex.xyz, 1.0);
	clip_vertex = gl_ClipVertex;
#endif
	
	texcoordDepth.zw = gl_Position.zw;
}
