#if GL_ES
	precision mediump float;
#endif

uniform vec4 collisionColor;

void main()
{
	gl_FragColor = collisionColor;
}