uniform sampler2D SkylineTexture;
varying vec4 texCoord;
void main()
{
	vec4 resultColor = vec4(1.0);
	texCoord /= texCoord.w;
	texCoord.xy = 0.5 * texCoord.xy + 0.5;

	float depth = texture2D(SkylineTexture, texCoord.xy).x;
	
	if (depth < 1.0)
		resultColor = vec4(86.0/255.0, 131.0/255.0, 65.0/255.0, 1.0);
	else
		resultColor = vec4(1.0,1.0,0.0,1.0);
	
	gl_FragColor = vec4(resultColor);
}