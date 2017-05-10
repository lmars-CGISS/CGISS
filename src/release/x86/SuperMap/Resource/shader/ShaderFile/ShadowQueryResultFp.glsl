#if GL_ES
	precision highp float;
#endif

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int times;
uniform int isFloatTex;

uniform float minValue;
uniform float maxValue;

varying vec4 renderTextureCoord;
varying vec2 tex0Coord;

float unpackIntFromVec4i(vec4 color)
{
	const vec4 bitShifts = vec4(1.0, 256.0, 256.0*256.0, 256.0*256.0*256.0);
	const vec4 c_bias = vec4(256.0, 256.0, 256.0, 256.0);
	return dot(color*c_bias, bitShifts);
}

void main()
{
	vec4 resultColor = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 texCoord = renderTextureCoord / renderTextureCoord.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	texCoord.y = 1.0 - texCoord.y;

	float density = 0.0;
	if ((texCoord.x<=1.0)&&(texCoord.x>=0.0)&&
		(texCoord.y<=1.0)&&(texCoord.y>=0.0))
	{
		vec4 texColor = texture2D(texture0, texCoord.xy);
		if (isFloatTex == 1)
		{
			density = texColor.r;
		}
		else
		{
			density = unpackIntFromVec4i(texColor);
		}
	}
	density = 1.0 - density / float(times);
	
	//if (density<minValue || density>maxValue)
	//{
		//discard;
	//}
	
	vec4 color = texture2D(texture1, vec2(0, density))
		* texture2D(texture2, tex0Coord.xy);
	if (color.a < 0.2)
	{
		discard;
		return;
	}
	gl_FragColor = color;
}
