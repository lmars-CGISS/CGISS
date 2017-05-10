// ´«ÈëÎÆÀí
uniform sampler2D texture0;
varying vec3 transperantBackColor;
varying float transperantBackColorTolerance;

void main()
{
	vec4 color = texture2D(texture0, gl_TexCoord[0].xy);

	if(transperantBackColorTolerance > 0.01)
	{
		float rDiff = abs(transperantBackColor.r - color.r);
		float gDiff = abs(transperantBackColor.g - color.g);
		float bDiff = abs(transperantBackColor.b - color.b);
		if(rDiff < transperantBackColorTolerance && gDiff < transperantBackColorTolerance && bDiff < transperantBackColorTolerance)
		{
			discard;
		}
	}

	gl_FragColor = color * gl_Color;
}