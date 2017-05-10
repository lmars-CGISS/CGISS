attribute vec4 vertex;
attribute vec4 colour;

uniform mat4 worldviewproj_matrix;

varying vec4 mixColor;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void main()
{
	// ¶¥µã×ø±ê±ä»»
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);	
	mixColor = colour;
	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}