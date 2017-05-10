#if GL_ES
	precision mediump float;
#endif

uniform sampler3D VolTexture;
uniform sampler2D ColorsTexture;
uniform float minValue;
uniform float maxValue;
uniform int bHasColorTable;

varying vec4 texCoord;

void main()
{
	if (texCoord.x > 1.0 || texCoord.x < 0.0
	|| texCoord.y > 1.0 || texCoord.y < 0.0
	|| texCoord.z > 1.0 || texCoord.z < 0.0)
	{
		discard;
	}

	float value = texture3D(VolTexture, texCoord.xyz).x;
	vec4 color = vec4(1.0,1.0,1.0,value);
	if (bHasColorTable)
	{
		if (value < minValue || value > maxValue)
		{
			discard;
		}
		value = (value - minValue) / (maxValue - minValue);
		value = clamp(value, 0.0, 1.0);
		color = texture2D(ColorsTexture, vec2(0.0, value));
	}

	color.a = 1.0;
	gl_FragColor = color;
}
