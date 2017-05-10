#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if GL_ES
precision mediump float;
varying vec4 color;
#else
uniform vec3 v3LightPos;
uniform float gMieConst;
uniform float gMieConst2;
varying vec3 v3Direction;
varying vec3 frontColor;
varying vec3 secondaryColor;
#endif

#ifndef GL_ES
// Calculates the Rayleigh phase function.
float getRayleighPhase(float cosAngle2)
{
	return 0.75 + 0.75 * cosAngle2;
}

// Calculates the Mie phase function.
float getMiePhase(float cosAngle, float cosAngle2)
{
	return 1.5 * ((1.0 - gMieConst2) / (2.0 + gMieConst2)) * (1.0 + cosAngle2) /
		pow(1.0 + gMieConst2 - 2.0 * gMieConst * cosAngle, 1.5);
}

// Returns the luminance of an RGB color.
float getLuminance(vec3 color)
{
	const vec3 luminance = vec3(0.3, 0.59, 0.11);
	return dot(luminance, color);
}
#endif
void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif

#ifndef GL_ES
	float fCosAngle = dot(v3LightPos, v3Direction) / length(v3Direction);
	float fCosAngle2 = fCosAngle*fCosAngle;
	
	vec4 color;
	color.rgb = getRayleighPhase(fCosAngle2) * frontColor + getMiePhase(fCosAngle, fCosAngle2) * secondaryColor;
	
	color.rgb = vec3(1.0) - exp(color.rgb * -3.0);
	
	float luminanceAlphaComponent = 2.0 * getLuminance(color.rgb);
	color.a = luminanceAlphaComponent + color.b;	
	
	gl_FragColor = color;
#else
	gl_FragColor = color;
#endif
}
