
#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;

varying float fTranslate[2];
varying float fScale;

varying float fMaxMipLev;
varying vec2 vecTileWidth;
varying float fWIndex;

void CalculateMipLevel(in vec2 inTexCoord, in vec2 vecTile, in float fMaxMip, inout float mipLevel)
{		
	// º∆À„ Mipmap Õº≤„
 	vec2 dx = dFdx(inTexCoord * vecTileWidth.x);
 	vec2 dy = dFdy(inTexCoord * vecTileWidth.y);

	float dotX = dot(dx, dx);
	float dotY = dot(dy, dy);
 	float dMax = max(dotX, dotY);
 	float dMin = min(dotX, dotY);
 	float offset = (dMax - dMin) / (dMax + dMin);
 	offset = clamp(offset, 0.0, 1.0);
 	float d = dMax * (1.0 - offset) + dMin * offset;
	
 	mipLevel = 0.5 * log2(d);
	mipLevel = clamp(mipLevel, 0.0, fMaxMip - 1.62);
}

void CalculateTexCoord(in vec2 inTexCoord, in float scale, in float XTran, in float YTran, in float fTile, in float mipLevel, inout vec2 outTexCoord)
{		
	vec2 fTexCoord = fract(inTexCoord);
	//pow(2, mipLevel)
	float fOffset = 1.0 * pow(2.0, mipLevel) / fTile;

	fTexCoord = clamp(fTexCoord, 0.0 + fOffset, 1.0 - fOffset);
	
	outTexCoord.x = (fTexCoord.x + XTran) * scale;
	outTexCoord.y = (fTexCoord.y + YTran) * scale;
}

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	vec4 FColor;
	vec2 vecTexCoord;

	float mipLevel = 0.0;
	CalculateMipLevel(gl_TexCoord[0].xy, vecTileWidth, fMaxMipLev, mipLevel);
	CalculateTexCoord(gl_TexCoord[0].xy, fScale, fTranslate[0], fTranslate[1], vecTileWidth.x, mipLevel, vecTexCoord);
	
	if(fWIndex < 3.6)
	{
		if(fWIndex < 1.6)
		{
			if(fWIndex < 0.6)
			{
				FColor = texture2DLod(texture0, vecTexCoord.xy, mipLevel);
			}
			else
			{
				FColor = texture2DLod(texture1, vecTexCoord.xy, mipLevel);
			}
		}
		else
		{
			if(fWIndex < 2.6)
			{
				FColor = texture2DLod(texture2, vecTexCoord.xy, mipLevel);
			}
			else
			{
				FColor = texture2DLod(texture3, vecTexCoord.xy, mipLevel);
			}
		}
	}
	else
	{
		if(fWIndex < 5.6)
		{
			if(fWIndex < 4.6)
			{
				FColor = texture2DLod(texture4, vecTexCoord.xy, mipLevel);
			}
			else
			{
				FColor = texture2DLod(texture5, vecTexCoord.xy, mipLevel);
			}
		}
		else
		{
			if(fWIndex < 6.6)
			{
				FColor = texture2DLod(texture6, vecTexCoord.xy, mipLevel);
			}
			else
			{
				FColor = texture2DLod(texture7, vecTexCoord.xy, mipLevel);
			}
		}
	}
	
//	FColor = texture2DLod(texture0, vecTexCoord.xy, mipLevel);
	
	if(FColor.a < 0.05)
	{
		discard;
	}
	
	gl_FragColor = FColor;
	gl_FragColor.rgb = gl_FragColor.rgb * gl_Color.rgb;	
}