#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

uniform sampler2D diffuseTexture;
uniform sampler2D secondTexture;
uniform float texCount;

#if ADDTEX
uniform sampler3D volumeTexture;
#endif

#if COLOR_TABLE
uniform sampler2D colorTableTexture;
uniform float minValue;
uniform float maxValue;
#endif

#if ALPHA_TEST
#include <lib/AlphaTest.glsllib>
uniform float alphaTestType;
#endif

varying vec4 vec4SelectionColor;

varying float fTexCoordTranslate[4];
varying float fTexCoordScale[2];
varying float fTexTileWidth[2];
varying float fMaxMipLev[2];

varying float fTexX;

void CalculateMipLevel(in vec2 inTexCoord, in float vecTile, in float fMaxMip, inout float mipLevel)
{		
	// ¼ÆËã Mipmap Í¼²ã
	vec2 dx = dFdx(inTexCoord * vecTile);
 	vec2 dy = dFdy(inTexCoord * vecTile);

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
	
	float fOffset = 1.0 * pow(2.0, mipLevel)/ fTile;
	
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
	vec2 vecTexCoord;
	float mipLevel = 0.0;
	
	vec4 FColor = vec4(1.0);
	vec4 SColor = vec4(1.0);
	int nTexIndex = 0;
	
	if(fTexX > -9999900.0)
	{
		if(texCount > 1.5)
		{
			nTexIndex = 2;
			CalculateMipLevel(gl_TexCoord[0].xy, fTexTileWidth[0], fMaxMipLev[0], mipLevel);
			CalculateTexCoord(gl_TexCoord[0].xy, fTexCoordScale[0], fTexCoordTranslate[0], fTexCoordTranslate[1], fTexTileWidth[0], mipLevel, vecTexCoord);
			FColor = texture2DLod(diffuseTexture, vecTexCoord, mipLevel);
		
			CalculateMipLevel(gl_TexCoord[1].xy, fTexTileWidth[1], fMaxMipLev[1], mipLevel);
			CalculateTexCoord(gl_TexCoord[1].xy, fTexCoordScale[1], fTexCoordTranslate[2], fTexCoordTranslate[3], fTexTileWidth[1], mipLevel, vecTexCoord);
			SColor = texture2DLod(secondTexture, vecTexCoord, mipLevel);
		}
		else if(texCount > 0.5)
		{
			nTexIndex = 1;
			CalculateMipLevel(gl_TexCoord[0].xy, fTexTileWidth[0], fMaxMipLev[0], mipLevel);
			CalculateTexCoord(gl_TexCoord[0].xy, fTexCoordScale[0], fTexCoordTranslate[0], fTexCoordTranslate[1], fTexTileWidth[0], mipLevel, vecTexCoord);
			FColor = texture2DLod(diffuseTexture, vecTexCoord, mipLevel);
		}
	}

	vec4 color = FColor * SColor;
	
	if(vec4SelectionColor.a < 0.1 || color.a < 0.1)
	{
		discard;
	}

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif
	
	gl_FragColor = color * vec4SelectionColor;
	

#if ADDTEX
	vec4 volumeColor = texture3D(volumeTexture, gl_TexCoord[nTexIndex].xyz);

#if COLOR_TABLE

	float value = volumeColor.r;
	
	if (value < minValue || value > maxValue)
	{
		volumeColor =  vec4(0.0);
	}
	else
	{
		value = (value - minValue) / (maxValue - minValue);
		value = clamp(value, 0.0, 1.0);

		volumeColor = texture2D(colorTableTexture, vec2(0.0, value));
	}

#endif

	if(gl_TexCoord[1].x < 0.0 || gl_TexCoord[1].x > 1.0 || gl_TexCoord[1].y < 0.0 || gl_TexCoord[1].y > 1.0 || gl_TexCoord[1].z < 0.0 || gl_TexCoord[1].z > 1.0)
	{
		volumeColor.rgb = vec3(1.0,1.0,1.0);
	}
	if(volumeColor.r < 0.01 && volumeColor.g < 0.01 && volumeColor.b < 0.01 )
	{
		volumeColor.rgb = vec3(1.0,1.0,1.0);
	}

	gl_FragColor.rgb = gl_FragColor.rgb * gl_Color.rgb * volumeColor.rgb;
#else
	gl_FragColor= gl_FragColor * gl_Color;
#endif

	if(gl_FragColor.a < 0.1)
	{
		discard;
	}
	
#if ALPHA_TEST
	AlphaTest(alphaTestType, gl_FragColor.a);
#endif
}
