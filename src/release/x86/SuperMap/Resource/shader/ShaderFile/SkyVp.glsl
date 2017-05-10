
attribute vec4 vertex;

uniform mat4 matManualWorldViewProj;
uniform vec3 v3CameraPos;
uniform vec3 v3LightPos;
uniform vec3 v3InvWavelength;
uniform float fCameraHeight;
uniform float fCameraHeight2;
uniform float fOuterRadius;
uniform float fOuterRadius2;
uniform float fInnerRadius;
uniform float fInnerRadius2;
uniform float fKrESun;
uniform float fKmESun;
uniform float fKr4PI;
uniform float fKm4PI;
uniform float fScale;
uniform float fScaleDepth;
uniform float fScaleOverScaleDepth;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

#if GL_ES
uniform float gMieConst;
uniform float gMieConst2;
varying vec4 color;
#else
varying vec3 v3Direction;
varying vec3 frontColor;
varying vec3 secondaryColor;
#endif

const float fPlanetRadius = 6378137.0;	// 地球半径
const int nSamples = 4;					// 采样数

// The scale equation calculated by Vernier's Graphical Analysis.
float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

// Returns the near intersection point of a line and a sphere
float getNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}
#if GL_ES
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
void main(void)
{
	// Get the ray from the camera to the vertex and its length (which is the far point of the ray passing through the atmosphere)
	vec3 v3Pos = vertex.xyz / fPlanetRadius;
	vec3 v3Ray = v3Pos - v3CameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;

	// Calculate the ray's starting position, then calculate its scattering offset
	vec3 v3Start = v3CameraPos;
	float fStartOffset = 0.0;
	if (fCameraHeight < fOuterRadius)
	{
		float fStartHeight = length(v3Start);
		float fStartDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
		float fStartAngle = dot(v3Ray, v3Start) / fStartHeight;
		fStartOffset = fStartDepth*scale(fStartAngle);		
	}
	else
	{
		float fNear = getNearIntersection(v3CameraPos, v3Ray, fCameraHeight2, fOuterRadius2);
		v3Start += v3Ray * fNear;
		fFar -= fNear;
		
		float fStartAngle = dot(v3Ray, v3Start) / fOuterRadius;
		float fStartDepth = exp(-1.0 / fScaleDepth);
		fStartOffset = fStartDepth*scale(fStartAngle);		
	}

	// Initialize the scattering loop variables
	float fSampleLength = fFar / float(nSamples);
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

	// Now loop through the sample rays
	vec3 v3FrontColor = vec3(0.0);
	for(int i=0; i<nSamples; i++)
	{
		float fSampleHeight = length(v3SamplePoint);
		float fSampleDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fSampleHeight));
		float fLightAngle = dot(v3LightPos, v3SamplePoint) / fSampleHeight;
		float fCameraAngle = dot(v3Ray, v3SamplePoint) / fSampleHeight;
		float fSampleScatter = (fStartOffset + fSampleDepth*(scale(fLightAngle) - scale(fCameraAngle)));
		vec3 v3Attenuate = exp(-fSampleScatter * (v3InvWavelength * fKr4PI + fKm4PI));
		v3FrontColor += v3Attenuate * (fSampleDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}

	// Finally, scale the Mie and Rayleigh colors and set up the varying variables for the pixel shader
	gl_Position = matManualWorldViewProj * vertex;
	gl_Position.z = min(gl_Position.z, gl_Position.w * 0.99999);
#if GL_ES
	// es把片元计算挪到顶点，提高性能，降低一点点效果
	vec3 vec3Rayleigh = v3FrontColor * (v3InvWavelength * fKrESun);
	vec3 vec3AdjustedMie = v3FrontColor * fKmESun;
	vec3 v3Direction = v3CameraPos - v3Pos;

	float fCosAngle = dot(v3LightPos, v3Direction) / length(v3Direction);
	float fCosAngle2 = fCosAngle*fCosAngle;
	
	color.rgb = getRayleighPhase(fCosAngle2) * vec3Rayleigh
		+ getMiePhase(fCosAngle, fCosAngle2) * vec3AdjustedMie;
	
	color.rgb = vec3(1.0) - exp(color.rgb * -3.0);
	
	float luminanceAlphaComponent = 2.0 * getLuminance(color.rgb);
	color.a = luminanceAlphaComponent + color.b;
#else
	frontColor = v3FrontColor * (v3InvWavelength * fKrESun);
	secondaryColor = v3FrontColor * fKmESun;
	v3Direction = v3CameraPos - v3Pos;
#endif	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
	
}