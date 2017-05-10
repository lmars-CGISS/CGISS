varying float fHeight;
uniform int isFloatTex;

vec4 packDepth(float depth)
{
  const vec4 c_bias = vec4(1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0, 0.0);

  float r = depth;
  float g = fract(r * 255.0);
  float b = fract(g * 255.0);
  float a = fract(b * 255.0);
  vec4 color = vec4(r, g, b, a);

  return color - (color.yzww * c_bias);
}

void main()
{
	if (isFloatTex == 1)
	{
		gl_FragColor = vec4(fHeight, fHeight, fHeight, 1.0);
	}
	else
	{
		gl_FragColor = packDepth(fHeight);
	}
}
