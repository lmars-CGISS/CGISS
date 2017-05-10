
uniform sampler2D elevationTexture;
uniform float FloatTexture;
varying vec2 elevationTexCoord;

void main()
{
	if (FloatTexture > 0.1)
	{
		gl_FragColor = vec4(texture2D(elevationTexture, elevationTexCoord.xy).x, 0.0, 0.0, 1.0);
	}
	else
	{
		gl_FragColor = texture2D(elevationTexture, elevationTexCoord.xy);
	}
}
