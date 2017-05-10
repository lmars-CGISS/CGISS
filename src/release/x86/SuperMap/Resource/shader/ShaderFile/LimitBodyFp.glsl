uniform vec4 limitBodyColor;
void main()
{
	gl_FragColor = limitBodyColor * gl_Color;
}