#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float surface_shininess;

varying float fTranslate[4];
varying float fScale[2];
varying float fMaxMipLev[2];
varying vec4 vecTileWidth;

void CalculateMipLevel(in vec2 inTexCoord, in vec2 vecTile, in float fMaxMip, inout float mipLevel)
{		
	// º∆À„ Mipmap Õº≤„
 	vec2 dx = dFdx(inTexCoord * vecTile.x);
 	vec2 dy = dFdy(inTexCoord * vecTile.y);

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
	vec4 FColor, SColor;
	vec2 vecTexCoord[2];

	float mipLevel1 = 0.0;
	CalculateMipLevel(gl_TexCoord[0].xy, vecTileWidth.xy, fMaxMipLev[0], mipLevel1);
	CalculateTexCoord(gl_TexCoord[0].xy, fScale[0], fTranslate[0], fTranslate[1], vecTileWidth.x, mipLevel1, vecTexCoord[0]);
	FColor = texture2DLod(texture0, vecTexCoord[0].xy, mipLevel1);

	float mipLevel2 = 0.0;
	CalculateMipLevel(gl_TexCoord[1].xy, vecTileWidth.zw, fMaxMipLev[1], mipLevel2);
	CalculateTexCoord(gl_TexCoord[1].xy, fScale[1], fTranslate[2], fTranslate[3], vecTileWidth.z, mipLevel2, vecTexCoord[1]);
	SColor = texture2DLod(texture1, vecTexCoord[1].xy, mipLevel2);	
	
	if(FColor.a < 0.05)
	{
		discard;
	}
	
	gl_FragColor.a = FColor.a;
	SColor.rgb = SColor.rgb + vec3(surface_shininess);
	SColor.rgb = clamp(SColor.rgb, vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));
	gl_FragColor.rgb = FColor.rgb * SColor.rgb * gl_Color.rgb;
}