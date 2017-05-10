#if GL_ES
	precision mediump float;
#endif

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

// 传入纹理
uniform sampler2D texture0;

varying vec4 texCoord;
varying vec4 mixColor;


#ifdef SHOW_OCEAN_WAVES

//波浪纹理
uniform sampler2D texture2;
//时钟
uniform float czm_frameNumber;

// low altitude wave settings
const float oceanFrequencyLowAltitude = 825000.0;
const float oceanAnimationSpeedLowAltitude = 0.004;
const float oceanOneOverAmplitudeLowAltitude = 0.5;

// high altitude wave settings
const float oceanFrequencyHighAltitude = 125000.0;
const float oceanAnimationSpeedHighAltitude = 0.008;
const float oceanOneOverAmplitudeHighAltitude = 0.5;

float linearFade(float edge0, float edge1, float x)
{
    return clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
}

vec4 czm_getWaterNoise(sampler2D normalMap, vec2 uv, float time, float angleInRadians)
{
    float cosAngle = cos(angleInRadians);
    float sinAngle = sin(angleInRadians);

    // time dependent sampling directions
    vec2 s0 = vec2(1.0/17.0, 0.0);
    vec2 s1 = vec2(-1.0/29.0, 0.0);
    vec2 s2 = vec2(1.0/101.0, 1.0/59.0);
    vec2 s3 = vec2(-1.0/109.0, -1.0/57.0);

    // rotate sampling direction by specified angle
    s0 = vec2((cosAngle * s0.x) - (sinAngle * s0.y), (sinAngle * s0.x) + (cosAngle * s0.y));
    s1 = vec2((cosAngle * s1.x) - (sinAngle * s1.y), (sinAngle * s1.x) + (cosAngle * s1.y));
    s2 = vec2((cosAngle * s2.x) - (sinAngle * s2.y), (sinAngle * s2.x) + (cosAngle * s2.y));
    s3 = vec2((cosAngle * s3.x) - (sinAngle * s3.y), (sinAngle * s3.x) + (cosAngle * s3.y));

    vec2 uv0 = (uv/103.0) + (time * s0);
    vec2 uv1 = uv/107.0 + (time * s1) + vec2(0.23);
    vec2 uv2 = uv/vec2(897.0, 983.0) + (time * s2) + vec2(0.51);
    vec2 uv3 = uv/vec2(991.0, 877.0) + (time * s3) + vec2(0.71);

    uv0 = fract(uv0);
    uv1 = fract(uv1);
    uv2 = fract(uv2);
    uv3 = fract(uv3);
    vec4 noise = (texture2D(normalMap, uv0)) +
                 (texture2D(normalMap, uv1)) +
                 (texture2D(normalMap, uv2)) +
                 (texture2D(normalMap, uv3));

    // average and scale to between -1 and 1
    return ((noise / 4.0) - 0.5) * 2.0;
}

#endif


#ifdef SHOW_REFLECTIVE_OCEAN

//使用海洋或陆地边界
uniform float u_useOceanBoundaryTexture;

//远处不显示波浪
uniform float u_wavesVisible;

//水体范围
uniform sampler2D texture1;
//水体纹理坐标
varying vec4 texCoordWater;

varying mat3 czm_normal3D;
varying vec3 v_positionMC;
varying vec3 v_positionEC;

uniform vec3 czm_sunDirectionEC;
uniform vec3 czm_moonDirectionEC;

const float czm_morphTime = 1.0;
const float u_zoomedOutOceanSpecularIntensity = 0.5;

const float oceanSpecularIntensity = 0.5;

const float czm_oneOverPi = 0.3183098861837907;
const float czm_oneOverTwoPi = 0.15915494309189535;

const vec3 waveHighlightColor = vec3(0.3, 0.45, 0.6);
const vec4 u_waterMaskTranslationAndScale = vec4(0.0,0.0,1.0,1.0);

vec2 czm_ellipsoidWgs84TextureCoordinates(vec3 normal)
{
    return vec2(atan(normal.y, normal.x) * czm_oneOverTwoPi + 0.5, asin(normal.z) * czm_oneOverPi + 0.5);
}

vec3 czm_geodeticSurfaceNormal(vec3 positionOnEllipsoid, vec3 ellipsoidCenter, vec3 oneOverEllipsoidRadiiSquared)
{
    return normalize((positionOnEllipsoid - ellipsoidCenter) * oneOverEllipsoidRadiiSquared);
}

mat3 czm_eastNorthUpToEyeCoordinates(vec3 positionMC, vec3 normalEC)
{
    vec3 tangentMC = normalize(vec3(-positionMC.y, positionMC.x, 0.0));  // normalized surface tangent in model coordinates
    vec3 tangentEC = normalize(czm_normal3D * tangentMC);                // normalized surface tangent in eye coordiantes
    vec3 bitangentEC = normalize(cross(normalEC, tangentEC));            // normalized surface bitangent in eye coordinates

    return mat3(
        tangentEC.x,   tangentEC.y,   tangentEC.z,
        bitangentEC.x, bitangentEC.y, bitangentEC.z,
        normalEC.x,    normalEC.y,    normalEC.z);
}

float czm_getSpecular(vec3 lightDirectionEC, vec3 toEyeEC, vec3 normalEC, float shininess)
{
    vec3 toReflectedLight = reflect(-lightDirectionEC, normalEC);
    float specular = max(dot(toReflectedLight, toEyeEC), 0.0);
    return pow(specular, shininess);
}

float czm_getLambertDiffuse(vec3 lightDirectionEC, vec3 normalEC)
{
    return max(dot(lightDirectionEC, normalEC), 0.0);
}

float waveFade(float edge0, float edge1, float x)
{
    float y = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return pow(1.0 - y, 5.0);
}

vec4 computeWaterColor(vec3 positionEyeCoordinates, vec2 textureCoordinates, mat3 enuToEye, vec4 imageryColor, float maskValue)
{
    vec3 positionToEyeEC = -positionEyeCoordinates;
    float positionToEyeECLength = length(positionToEyeEC);

    // The double normalize below works around a bug in Firefox on Android devices.
    vec3 normalizedpositionToEyeEC = normalize(normalize(positionToEyeEC));
    
    // Fade out the waves as the camera moves far from the surface.
    float waveIntensity = waveFade(70000.0, 1000000.0, positionToEyeECLength);

	vec3 normalTangentSpace = vec3(0.0, 0.0, 1.0);

	if(u_wavesVisible > 0.5)
	{
#ifdef SHOW_OCEAN_WAVES
		// high altitude waves
		float time = czm_frameNumber * oceanAnimationSpeedHighAltitude;
		vec4 noise = czm_getWaterNoise(texture2, textureCoordinates * oceanFrequencyHighAltitude, time, 0.0);
		vec3 normalTangentSpaceHighAltitude = vec3(noise.xy, noise.z * oceanOneOverAmplitudeHighAltitude);
    
		// low altitude waves
		time = czm_frameNumber * oceanAnimationSpeedLowAltitude;
		noise = czm_getWaterNoise(texture2, textureCoordinates * oceanFrequencyLowAltitude, time, 0.0);
		vec3 normalTangentSpaceLowAltitude = vec3(noise.xy, noise.z * oceanOneOverAmplitudeLowAltitude);
    
		// blend the 2 wave layers based on distance to surface
		float highAltitudeFade = linearFade(0.0, 60000.0, positionToEyeECLength);
		float lowAltitudeFade = 1.0 - linearFade(20000.0, 60000.0, positionToEyeECLength);
		normalTangentSpace = 
			(highAltitudeFade * normalTangentSpaceHighAltitude) + 
			(lowAltitudeFade * normalTangentSpaceLowAltitude);
		normalTangentSpace = normalize(normalTangentSpace);
    
		// fade out the normal perturbation as we move farther from the water surface
		normalTangentSpace.xy *= waveIntensity;
		normalTangentSpace = normalize(normalTangentSpace);
#else
		normalTangentSpace = vec3(0.0, 0.0, 1.0);
#endif
	}

    vec3 normalEC = enuToEye * normalTangentSpace;

    // Use diffuse light to highlight the waves
    float diffuseIntensity = czm_getLambertDiffuse(czm_sunDirectionEC, normalEC) * maskValue;
    vec3 diffuseHighlight = waveHighlightColor * diffuseIntensity;
    
	vec3 nonDiffuseHighlight = vec3(0.0);

	if(u_wavesVisible > 0.5)
	{
#ifdef SHOW_OCEAN_WAVES
		// Where diffuse light is low or non-existent, use wave highlights based solely on
		// the wave bumpiness and no particular light direction.
		float tsPerturbationRatio = normalTangentSpace.z;
		nonDiffuseHighlight = mix(waveHighlightColor * 5.0 * (1.0 - tsPerturbationRatio), vec3(0.0), diffuseIntensity);
#else
		nonDiffuseHighlight = vec3(0.0);
#endif
	}
    // Add specular highlights in 3D, and in all modes when zoomed in.
    float specularIntensity = czm_getSpecular(czm_sunDirectionEC, normalizedpositionToEyeEC, normalEC, 10.0) + 0.25 * czm_getSpecular(czm_moonDirectionEC, normalizedpositionToEyeEC, normalEC, 10.0);
    float surfaceReflectance = mix(0.0, mix(u_zoomedOutOceanSpecularIntensity, oceanSpecularIntensity, waveIntensity), maskValue);
    float specular = specularIntensity * surfaceReflectance;
    
    return vec4(imageryColor.rgb + diffuseHighlight + nonDiffuseHighlight + specular, imageryColor.a); 
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
	vec4 texColor = texture2D(texture0, texCoord.xy);
	texColor.a = 1.0;
	vec4 color = texColor* mixColor;

#ifdef SHOW_REFLECTIVE_OCEAN
    vec3 normalMC = normalize(czm_geodeticSurfaceNormal(v_positionMC, vec3(0.0), vec3(1.0)));   // normalized surface normal in model coordinates
    vec3 normalEC = normalize(czm_normal3D * normalMC);                                         // normalized surface normal in eye coordiantes

    vec2 waterMaskTranslation = u_waterMaskTranslationAndScale.xy;
    vec2 waterMaskScale = u_waterMaskTranslationAndScale.zw;
    vec2 waterMaskTextureCoordinates = texCoordWater.xy * waterMaskScale + waterMaskTranslation;

    float mask = texture2D(texture1, waterMaskTextureCoordinates).r;

	if(u_useOceanBoundaryTexture > 0.5)
	{
		mask = 1.0 - mask;
	}

    if (mask > 0.0)
    {
        mat3 enuToEye = czm_eastNorthUpToEyeCoordinates(v_positionMC, normalEC);
        
        vec2 ellipsoidTextureCoordinates = czm_ellipsoidWgs84TextureCoordinates(normalMC);
        vec2 ellipsoidFlippedTextureCoordinates = czm_ellipsoidWgs84TextureCoordinates(normalMC.zyx);

        vec2 textureCoordinates = mix(ellipsoidTextureCoordinates, ellipsoidFlippedTextureCoordinates, czm_morphTime * smoothstep(0.9, 0.95, normalMC.z));

        color = computeWaterColor(v_positionEC, textureCoordinates, enuToEye, color, mask);
    }
#endif

	gl_FragColor = color;
}
