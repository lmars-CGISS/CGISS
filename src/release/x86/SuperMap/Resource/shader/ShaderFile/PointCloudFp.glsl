#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

#if ALPHA_TEST
#include <lib/AlphaTest.glsllib>
uniform float alphaTestType;
#endif

varying vec4 vec4SelectionColor;
uniform int contourFillMode;
uniform sampler2D hypsometricTexture;
uniform float opacity;
uniform float floor;
uniform float ceil;
uniform float maxVisibleValue;
uniform float minVisibleValue;
uniform int hasColorTable;
varying float wValue;

vec4 computHypsometricColor()
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
	if(vec4SelectionColor.a < 0.1 || gl_Color.a < 0.1)
	{
		discard;
	}
	
#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif
	gl_FragColor = gl_Color;// * vec4SelectionColor;
	if(hasColorTable == 1 && contourFillMode != 0)
	{	
		// 如果点不在阈值范围内时，丢弃并返回
		if(wValue < minVisibleValue || wValue > maxVisibleValue)
		{
			discard;
			return;
		}
		vec4 hypsometricColor = vec4(0.0);
		float finalOpacity = opacity;
		hypsometricColor = computHypsometricColor();
		gl_FragColor = gl_FragColor * vec4(hypsometricColor.rgb,opacity);
	}
	if(gl_FragColor.a < 0.1)
	{
		discard;
		return;
	}
#if ALPHA_TEST
	AlphaTest(alphaTestType, gl_FragColor.a);
#endif
}
