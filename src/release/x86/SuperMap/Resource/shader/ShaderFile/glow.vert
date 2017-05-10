#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0].x = gl_Color.a;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}