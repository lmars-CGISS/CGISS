
uniform sampler2D texture0;
uniform vec4 texture0_size;

varying vec2 texCoord;
varying vec4 backColor;
varying float colorTolerance;

const float fTexOffset = 0.001953125;

void CalculateTexCoord(in vec2 inTexCoord, inout vec2 outTexCoord, inout vec2 outAlphaTexCoord)
{		
	outTexCoord.x = inTexCoord.x;
	outAlphaTexCoord.x = inTexCoord.x;
	
	outTexCoord.y = inTexCoord.y * 0.5;
	outTexCoord.y = clamp(outTexCoord.y, 0.0, 0.5 - fTexOffset);
	
	outAlphaTexCoord.y = inTexCoord.y * 0.5 + 0.5;
	outAlphaTexCoord.y = clamp(outAlphaTexCoord.y, 0.5 + fTexOffset, 1.0);
}

void main()
{	
	vec4 color;
	if(abs(texture0_size.y / texture0_size.x - 2.0) < 0.0001) 
	{
		vec2 vecTexCoord;
		vec2 vecAlphaTexCoord;
		CalculateTexCoord(texCoord, vecTexCoord, vecAlphaTexCoord);
		color = texture2D(texture0, vecTexCoord);
		color.a = texture2D(texture0, vecAlphaTexCoord).r;
	}
	else
	{
		color = texture2D(texture0, texCoord);
	}
	
	float rDiff = abs(backColor.r - color.r);
	float gDiff = abs(backColor.g - color.g);
	float bDiff = abs(backColor.b - color.b);
	if ((rDiff < colorTolerance && gDiff < colorTolerance && bDiff < colorTolerance)
		|| color.a < 0.2)
	{
		discard;
	}
	
	gl_FragColor = color;
}
