#if GL_ES
	precision mediump float;
#endif

uniform sampler2D texture0;
uniform vec4 foreColor;
uniform vec4 backColor;

varying vec4 texCoord;

void main()
{
	vec4 color = texture2D(texture0, texCoord.xy);
	if (color.a < 0.2)
	{
		color = backColor;
	}
	else
	{
		color = foreColor * color;
	}
	gl_FragColor = color;
}