#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

uniform sampler2D diffuseTexture;
uniform float texCount;

uniform sampler2D hypsometricTexture;
uniform sampler2D hypsometricRenderTexture;

uniform int contourFillMode;
uniform float contourInterval;
uniform vec4 lineColor;//等高线的颜色
uniform float opacity;
uniform float floor;
uniform float ceil;
uniform float maxVisibleValue;
uniform float minVisibleValue;
uniform int hasColorTable;

varying float wValue;
varying vec2 hypTexCoord;
varying float bHashHyp;

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

float computeMixCon()
{
	//等高线和登高分层设色
	float distanceToContour = mod(wValue-0.0002, contourInterval);
	float dxc = abs(dFdx(wValue));
	float dyc = abs(dFdy(wValue));
	float dF = max(dxc, dyc);
	return (distanceToContour < dF)?1.0:0.0;
}

vec4 computContourMapColor()
{
	float threshold = clamp(abs(ceil-floor),0.000001,20000.0);
	float contourRate = (wValue-floor)/threshold;
	float finalCoord = clamp(contourRate,0.0,1.0);
	vec2 contourCoord = vec2(0, finalCoord);
	return texture2D(hypsometricTexture, contourCoord).rgba;
}

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	vec4 color = vec4(1.0);
	int nTexIndex = 0;
	
	if(gl_TexCoord[0].x < -999.0)
	{
		color.rgb = vec3(0.5);
	}
	else if(texCount > 0.5)
	{
		nTexIndex = 1;
		color = texture2D(diffuseTexture, gl_TexCoord[0].xy);
	}
	
#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	gl_FragColor = color;

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
	gl_FragColor = gl_FragColor * gl_Color;
#endif
	
	if(hasColorTable == 1)
	{	
		if(bHashHyp > 0.1)
		{
			vec4 hypColor = texture2D(hypsometricRenderTexture, hypTexCoord);
			if(hypColor.r < 0.1)
			{
				if(gl_FragColor.a < 0.1)
				{
					discard;
				}
				
				#if ALPHA_TEST
					AlphaTest(alphaTestType, gl_FragColor.a);
				#endif
				return;
			}
		}
		
		// 如果点在可是高度范围内且是合法值
		vec4 contourMapColor = vec4(0.0);
		float finalOpacity = opacity;
		if (wValue <= maxVisibleValue && wValue >= minVisibleValue)
		{
			if(contourFillMode == 1)
			{
				contourMapColor = computContourMapColor();
			}
			else if(contourFillMode == 2)
			{
				finalOpacity = computeMixCon();
				contourMapColor = lineColor;
			}
			else if(contourFillMode == 3)
			{
				float mix_con = computeMixCon();
				contourMapColor = mix(computContourMapColor(), lineColor, mix_con);
			}
			else
			{
				finalOpacity = 0.0;
			}
		}
		else
		{
			finalOpacity = 0.0;
		}
	
		// 纹理颜色
		vec4 finalColor = mix(gl_FragColor, contourMapColor, finalOpacity);
	
		gl_FragColor = finalColor;
	}
	
	if(gl_FragColor.a < 0.1)
	{
		discard;
	}
	
#if ALPHA_TEST
	AlphaTest(alphaTestType, gl_FragColor.a);
#endif
}
