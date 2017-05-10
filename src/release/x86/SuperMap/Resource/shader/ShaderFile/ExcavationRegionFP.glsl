uniform sampler2D texture0;
void main()
{
	vec4 color = texture2D(texture0, gl_TexCoord[0].xy);
	gl_FragColor = color;
}
