#if SCISSOR_TEST
varying vec4 vPosition;
#endif
attribute vec4 vertex;
attribute vec4 colour;

uniform vec4 surface_diffuse_colour;

varying vec4 mixColor;

void main()
{
	// ¶¥µã×ø±ê±ä»»
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
	mixColor = colour * surface_diffuse_colour;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
