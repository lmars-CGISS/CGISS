#define DETAIL
#define DETAIL_OCTAVE 2.0
#define DETAIL_BLEND 0.4
//#define VISUALIZE_HEIGHT
#define SPECULAR_BOOST 500.0
#define SPECULAR_DISTANCE_FACTOR 70.0
#define BUBBLES 0.1

#ifdef OPENGL32
in vec3 V;
in vec2 foamTexCoords;
in vec2 texCoords;
in vec2 noiseTexCoords;
in float fogFactor;
in vec3 wakeSlopeAndFoam;
#ifdef PROPELLER_WASH
in vec3 washTexCoords;
#endif
in float transparency;
in float depth;
#ifdef BREAKING_WAVES
in float breaker;
in float breakerFade;
in vec2 breakerTexCoords;
#endif
#ifdef LEEWARD_DAMPENING
in float leewardDampening;
#endif
in vec4 vVertex_Eye_Space;
in vec4 vVertex_Projection_Space;
#ifdef PER_FRAGMENT_PROP_WASH
in vec3 propWashCoord;
#endif
#else
varying vec3 V;
varying vec2 foamTexCoords;
varying vec2 texCoords;
varying vec2 noiseTexCoords;
varying float fogFactor;
varying vec3 wakeSlopeAndFoam;
#ifdef PROPELLER_WASH
varying vec3 washTexCoords;
#endif
varying float transparency;
varying float depth;
#ifdef BREAKING_WAVES
varying float breaker;
varying float breakerFade;
varying vec2 breakerTexCoords;
#endif
#ifdef LEEWARD_DAMPENING
varying float leewardDampening;
#endif
varying vec4 vVertex_Projection_Space;
varying vec4 vVertex_Eye_Space;
#ifdef PER_FRAGMENT_PROP_WASH
varying vec3 propWashCoord;
#endif
#endif

uniform vec3 trit_L;
uniform vec3 trit_lightColor;
uniform vec3 trit_ambientColor;
uniform vec3 trit_refractColor;
uniform float trit_shininess;
uniform bool trit_hasEnvMap;
uniform sampler2D trit_slopeFoamMap;
uniform mat3 trit_basis;
uniform mat3 trit_invBasis;
uniform samplerCube trit_cubeMap;
uniform sampler2D trit_lightFoamTex;
uniform sampler2D trit_noiseTex;
uniform sampler2D trit_washTex;
uniform float trit_noiseAmplitude;
uniform mat3 trit_cubeMapMatrix;
uniform float trit_invNoiseDistance;
uniform sampler2D trit_planarReflectionMap;
uniform bool trit_hasPlanarReflectionMap;
uniform mat3 trit_planarReflectionMapMatrix;
uniform float trit_planarReflectionDisplacementScale;
uniform float trit_foamBlend;
uniform vec3 trit_fogColor;
uniform float trit_textureLODBias;
uniform bool trit_hasHeightMap;
uniform bool trit_hasUserHeightMap;
uniform float trit_planarReflectionBlend;
uniform bool trit_depthOnly;
uniform bool trit_underwater;
uniform vec3 trit_doubleRefractionColor;
uniform float trit_doubleRefractionIntensity;
uniform float trit_oneOverGamma;
uniform float trit_sunIntensity;
uniform float trit_reflectivityScale;
uniform float trit_transparency;

#ifdef BREAKING_WAVES
uniform sampler2D trit_breakerTex;
#endif

#ifdef HIGHALT
uniform float trit_invZoom;
#endif

#ifdef PER_FRAGMENT_PROP_WASH
struct trit_CircularWave {
    float amplitude;
    float radius;
    float k;
    float halfWavelength;
    vec3 position;
};

struct trit_KelvinWake {
    float amplitude;
    vec3 position;
    vec3 shipPosition;
    float foamAmount;
};


struct trit_PropWash {
    vec3 deltaPos;
    float washWidth;
    vec3 propPosition;
    float distFromSource;
    float washLength;
    float alphaStart;
    float alphaEnd;
};

struct trit_LeewardDampener {
    vec3 bowPos;
    vec3 sternPos;
    float velocityDampening;
};

#ifdef USE_UBO
layout(std140) uniform trit_WakeParameters {
#ifdef PROPELLER_WASH
    trit_PropWash trit_washes[MAX_PROP_WASHES];
#endif

    trit_CircularWave trit_circularWaves[MAX_CIRCULAR_WAVES];

    trit_KelvinWake trit_wakes[MAX_KELVIN_WAKES];

#ifdef LEEWARD_DAMPENING
    trit_LeewardDampener trit_leewardDampeners[MAX_LEEWARD_DAMPENERS];
    int trit_numLeewardDampeners;
    float trit_leewardDampeningStrength;
#endif

    int trit_numPropWashes;
    int trit_numKelvinWakes;
    int trit_numCircularWaves;

    bool trit_doWakes;
    float trit_washLength;
};
#else
#ifdef PROPELLER_WASH
uniform trit_PropWash trit_washes[MAX_PROP_WASHES];
#endif

uniform trit_CircularWave trit_circularWaves[MAX_CIRCULAR_WAVES];

uniform trit_KelvinWake trit_wakes[MAX_KELVIN_WAKES];

#ifdef LEEWARD_DAMPENING
uniform trit_LeewardDampener trit_leewardDampeners[MAX_LEEWARD_DAMPENERS];
uniform int trit_numLeewardDampeners;
uniform float trit_leewardDampeningStrength;
#endif

uniform int trit_numPropWashes;
uniform int trit_numKelvinWakes;
uniform int trit_numCircularWaves;
uniform bool trit_doWakes;
uniform float trit_washLength;
#endif
#endif // PER_FRAGMENT_PROP_WASH

// From user-functions.glsl:
void user_lighting(in vec3 L
                   , in vec3 vVertex_World_Space, in vec3 vNormal_World_Space
                   , in vec4 vVertex_Projection_Space
                   , inout vec3 ambient, inout vec3 diffuse, inout vec3 specular);
void user_fog(in vec3 vNorm, inout vec4 waterColor, inout vec4 fogColor, inout float fogBlend);
void user_tonemap(in vec4 preToneMapColor, inout vec4 postToneMapColor);
void user_reflection_adjust(in vec4 envColor, in vec4 planarColor, in float planarReflectionBlend, inout vec4 reflectedColor);
float user_cloud_shadow_fragment();
void writeFragmentData(in vec4 finalColor, in vec4 Cdiffuse, in vec3 lightColor, in vec3 nNorm);
void user_diffuse_color( inout vec3 Cdiffuse, in vec3 CiNoLight, in vec4 reflectedColor,
                         in float reflectivity );

#ifdef PER_FRAGMENT_PROP_WASH
vec3 applyPropWash(in vec3 v, in vec3 finalAmbient)
{
    vec3 texCoords = vec3(0.0, 0.0, 0.0);
    vec3 Cw = vec3(0.0, 0.0, 0.0);
#ifdef PROPELLER_WASH

    float numHits = 0.0;
    for (int i = 0; i < trit_numPropWashes; i++) {

        //if (washes[i].distFromSource == 0) continue;

        vec3 C = trit_washes[i].deltaPos;
        vec3 A = v - trit_washes[i].propPosition;
        float segmentLength = length(C);

        // Compute t
        float t0 = dot(C, A) / dot(C, C);

        // Compute enough overlap to account for curved paths.
        float overlap = (trit_washes[i].washWidth / segmentLength) * 0.5;

        if (t0 >= -overlap && t0 <= 1.0 + overlap) {

            // Compute distance from source
            float distFromSource = trit_washes[i].distFromSource - (1.0 - t0) * segmentLength;

            // Compute wash width
            float washWidth = (trit_washes[i].washWidth * pow(distFromSource, 1.0 / 4.5)) * 0.5;

            // Compute distance to line
            vec3 B = A - C;
            vec3 aCrossB = cross(A, B);
            float d = length(aCrossB) / segmentLength;

            // The direction of A X B indicates if we're 'left' or 'right' of the path
            float nd = d / washWidth;

            if (clamp(nd, 0.0, 1.0) == nd) {
                texCoords.x = nd;
                // The t0 parameter from our initial distance test to the line segment makes
                // for a handy t texture coordinate
                texCoords.y =  (trit_washes[i].washLength - distFromSource) / trit_washes[i].washWidth;

                // We stuff the blend factor into the r coordinate.

                float blend = mix(trit_washes[i].alphaEnd, trit_washes[i].alphaStart, t0);
                blend *= max(0.0, 1.0 - nd * nd);
                texCoords.z = clamp(blend, 0.0, 1.0);

#ifdef OPENGL32
                Cw += texture(trit_washTex, texCoords.xy).xyz * finalAmbient * texCoords.z;
#else
                Cw += texture2D(trit_washTex, texCoords.xy).xyz * finalAmbient * texCoords.z;
#endif
                numHits += 1.0;
            }
        }
    }
#endif
    return numHits > 0.0 ? Cw / numHits : Cw;
}
#endif


void main()
{
#ifdef VISUALIZE_HEIGHT
    float rr = (-depth / 100.0) + 0.5;
    rr = clamp(rr, 0.0, 1.0);
    gl_FragColor = vec4(rr, rr, rr, 1.0);
    return;
#endif

    bool hasHeightMap = ( trit_hasHeightMap || trit_hasUserHeightMap );
    if (hasHeightMap && depth < 0) {
        discard;
        return;
    }

    if (trit_depthOnly) {
#ifdef OPENGL32
        writeFragmentData(vec4(0,0,0,1), vec4(0,0,0,0), trit_lightColor, vec3(0,0,0));
#else
        gl_FragColor = vec4(0,0,0,1);
#endif
        return;
    }

    const float IOR = 1.33333;

    float tileFade = exp(-length(V) * trit_invNoiseDistance);
    float horizDist = length((trit_basis * V).xy);
    float horizDistNorm = horizDist * trit_invNoiseDistance;
    float tileFadeHoriz = exp(-horizDistNorm);

    vec3 vNorm = normalize(V);
#ifdef OPENGL32

#ifdef HIGHALT
    vec4 slopesAndFoamHigh = texture(trit_slopeFoamMap, texCoords, trit_textureLODBias).xyzw;
    vec4 slopesAndFoamMed = texture(trit_slopeFoamMap, (texCoords + 0.1) * 0.25, trit_textureLODBias).xyzw;
    vec4 slopesAndFoamLow = texture(trit_slopeFoamMap, (texCoords + 0.7) * 0.125, trit_textureLODBias).xyzw;
    vec4 slopesAndFoamReallyLow = texture(trit_slopeFoamMap, (texCoords + 0.3) * 0.0625, trit_textureLODBias).xyzw;
    float altitude = abs((trit_basis * V).z) * trit_invZoom;
    float invBlendDist = 10.0 * trit_invNoiseDistance * trit_invZoom;
    float amp = 1.0 - min(1.0, altitude * invBlendDist);
    vec4 slopesAndFoam = slopesAndFoamHigh * amp;
    float totalAmp = amp;
    amp = min(0.5, altitude * invBlendDist);
    slopesAndFoam += slopesAndFoamMed * amp;
    totalAmp += amp;
    amp = min(0.5, altitude * invBlendDist * 0.5);
    slopesAndFoam += slopesAndFoamLow * amp;
    totalAmp += amp;
    amp = min(0.5, altitude *invBlendDist * 0.25);
    slopesAndFoam += slopesAndFoamReallyLow * amp;
    totalAmp += amp;

    slopesAndFoam /= totalAmp;
#else // HIGHALT
    vec4 slopesAndFoam = texture(trit_slopeFoamMap, texCoords, trit_textureLODBias).xyzw;
#endif // HIGHALT

    float fresnelScale = length(slopesAndFoam.xyz);

#ifdef DETAIL
    for (int n = 1; n <= NUM_OCTAVES; n++) {
        slopesAndFoam.xyz += texture(trit_slopeFoamMap, texCoords * DETAIL_OCTAVE * n, trit_textureLODBias).xyz * DETAIL_BLEND;
    }
#endif // DETAIL
    vec3 unscaledNoise = normalize( texture(trit_noiseTex, noiseTexCoords).xyz - vec3(0.5, 0.5, 0.5) );
#else // OPENGL32

#ifdef HIGHALT
    vec4 slopesAndFoamHigh = texture2D(trit_slopeFoamMap, texCoords, trit_textureLODBias).xyzw;
    vec4 slopesAndFoamMed = texture2D(trit_slopeFoamMap, (texCoords + 0.1) * 0.25, trit_textureLODBias).xyzw;
    vec4 slopesAndFoamLow = texture2D(trit_slopeFoamMap, (texCoords + 0.7) * 0.125, trit_textureLODBias).xyzw;
    vec4 slopesAndFoamReallyLow = texture2D(trit_slopeFoamMap, (texCoords + 0.3) * 0.0625, trit_textureLODBias).xyzw;
    float altitude = abs((trit_basis * V).z) * trit_invZoom;
    float invBlendDist = 10.0 * trit_invNoiseDistance * trit_invZoom;

    float amp = 1.0 - min(1.0, altitude * invBlendDist);
    vec4 slopesAndFoam = slopesAndFoamHigh * amp;
    float totalAmp = amp;
    amp = min(0.5, altitude * invBlendDist);
    slopesAndFoam += slopesAndFoamMed * amp;
    totalAmp += amp;
    amp = min(0.5, altitude * invBlendDist * 0.5);
    slopesAndFoam += slopesAndFoamLow * amp;
    totalAmp += amp;
    amp = min(0.5, altitude *invBlendDist * 0.25);
    slopesAndFoam += slopesAndFoamReallyLow * amp;
    totalAmp += amp;

    slopesAndFoam /= totalAmp;
#else // HIGHALT
    vec4 slopesAndFoam = texture2D(trit_slopeFoamMap, texCoords, trit_textureLODBias).xyzw;
#endif // HIGHALT
    // Uncomment to visualize Jacobian
    //gl_FragColor = vec4(slopesAndFoam.z, slopesAndFoam.z, slopesAndFoam.z, 1.0);
    //return;

    float fresnelScale = length(slopesAndFoam.xyz);

#ifdef DETAIL
    for (int n = 1; n <= NUM_OCTAVES; n++) {
        slopesAndFoam.xyz += texture2D(trit_slopeFoamMap, texCoords * DETAIL_OCTAVE * n, trit_textureLODBias).xyz * DETAIL_BLEND;
    }
#endif // DETAIL
    vec3 unscaledNoise = normalize(texture2D(trit_noiseTex, noiseTexCoords).xyz - vec3(0.5, 0.5, 0.5) );
#endif // else OPENGL32

    vec3 normalNoise = unscaledNoise * trit_noiseAmplitude;
    normalNoise.z = abs( normalNoise.z );

    slopesAndFoam.xyz = normalize(slopesAndFoam.xyz);
    vec4 finalSlopesAndFoam = slopesAndFoam;
#ifdef LEEWARD_DAMPENING
    finalSlopesAndFoam.xyz = mix(vec3(0.0,0.0,1.0), finalSlopesAndFoam.xyz, leewardDampening);
    finalSlopesAndFoam.w *= leewardDampening;
#endif

    vec3 wx = vec3(1.0, 0.0, wakeSlopeAndFoam.x);
    vec3 wy = vec3(0.0, 1.0, wakeSlopeAndFoam.y);
    vec3 wakeNormal = normalize(cross(wx, wy));

#ifdef BREAKING_WAVES
    vec3 realNormal = mix(vec3(0.0,0.0,1.0), finalSlopesAndFoam.xyz, breakerFade);
#else
    vec3 realNormal = finalSlopesAndFoam.xyz;
#endif
    realNormal = normalize(realNormal + wakeNormal);

#ifdef SPARKLE
    float bias = horizDistNorm * horizDistNorm * -64.0;
    bias = mix(bias, -5.0, clamp(altitude * invBlendDist, 0.0, 1.0));
#ifdef OPENGL32
    vec3 specularSlopes = texture(trit_slopeFoamMap, texCoords, bias).xyz;
#else
    vec3 specularSlopes = texture2D(trit_slopeFoamMap, texCoords, bias).xyz;
#endif
    vec3 specNormal = trit_invBasis * normalize(specularSlopes);
#endif

    vec3 fadedNormal = mix(vec3(0.0,0.0,1.0), realNormal, tileFadeHoriz);

    vec3 nNorm = trit_invBasis * normalize(fadedNormal + (normalNoise * (1.0 - tileFade)));

    vec3 P = reflect(vNorm, nNorm);

#if 0
    float reflectionHalfSphere = dot( P, trit_invBasis[2] /* == trit_invBasis * vec3(0,0,1) */ );

    if( reflectionHalfSphere < 0. ) { // make secondary reflection if reflected vector points down
        P = reflect(P, nNorm);
    }
#endif

#ifdef FAST_FRESNEL
    //float reflectivity = clamp( 0.02+0.97*pow((1.0-dot(P, nNorm)),5.0), 0.0, 1.0 );

    float r=(1.2-1.0)/(1.2+1.0);
    float reflectivity = max(0.0,min(1.0,r+(1.0-r)*pow((1.0-dot(nNorm,P)) * fresnelScale, 4.0)));

#else
    vec3 S = refract(P, nNorm, 1.0 / IOR);

    float cos_theta1 = (dot(P, nNorm));
    float cos_theta2 = (dot(S, -nNorm));

    float Fp = (cos_theta1 - (IOR * cos_theta2)) /
               ((IOR * cos_theta2) + cos_theta1);
    float Fs = (cos_theta2 - (IOR * cos_theta1)) /
               ((IOR * cos_theta1) + cos_theta2);
    Fp = Fp * Fp;
    Fs = Fs * Fs;

    float reflectivity = clamp((Fs + Fp) * 0.5, 0.0, 1.0);
#endif

    // No reflections on foam.
    reflectivity = mix(reflectivity, 0.0, clamp(wakeSlopeAndFoam.z, 0.0, 1.0));

    reflectivity *= trit_reflectivityScale;

    vec4 envColor;

    if (trit_hasEnvMap) {
        P = trit_basis * P;
        P.z = max(0, P.z);
        P = trit_invBasis * normalize(P);

#ifdef OPENGL32
        envColor = textureLod(trit_cubeMap, trit_cubeMapMatrix * P, 0);
#else
        envColor = textureCubeLod(trit_cubeMap, trit_cubeMapMatrix * P, 0);
#endif
    } else {
        envColor = vec4(trit_ambientColor, 1.0);
    }

    vec4 reflectedColor = envColor;

    if( trit_hasPlanarReflectionMap ) {
        vec3 up = trit_invBasis[2]; // == trit_invBasis * vec3( 0.0, 0.0, 1.0 )
        // perturb view vector by normal xy coords multiplied by displacement scale
        // when we do it in world oriented space this perturbation is equal to:
        // ( nNorm - dot( nNorm, up ) * up ) == trit_invBasis * vec3( ( trit_basis * nNorm ).xy, 0 )
        vec3 vNormPerturbed = vNorm + ( nNorm - dot( nNorm, up ) * up ) * trit_planarReflectionDisplacementScale;
        vec3 tc = trit_planarReflectionMapMatrix * vNormPerturbed;
#ifdef OPENGL32
        vec4 planarColor = textureProj( trit_planarReflectionMap, tc );
#else
        vec2 tcProj = vec2(tc.x / tc.z, tc.y / tc.z);
        vec4 planarColor = texture2D(trit_planarReflectionMap, tcProj);
#endif

        //planarColor.a = planarColor.a > 0.9 ? planarColor.a : 0;

        reflectedColor = mix( envColor, planarColor, planarColor.a * trit_planarReflectionBlend);

        user_reflection_adjust(envColor, planarColor, trit_planarReflectionBlend, reflectedColor);
    } else {
        user_reflection_adjust(envColor, vec4(0.0,0.0,0.0,0.0), 1.0, reflectedColor);
    }

    // This makes the water more visually interesting. For realism, comment out.
    //reflectivity = pow(reflectivity, 0.8);

    vec3 finalAmbient = trit_ambientColor;
    vec3 finalDiffuse = trit_lightColor * max(0,dot(trit_L, nNorm));

    vec3 refractedLight, LNorm;

    if (trit_underwater) {
        LNorm = normalize(trit_L);
        refractedLight = refract(LNorm, trit_invBasis[2], 1.0 / 1.333);
        nNorm = -nNorm;
    } else {
        refractedLight = LNorm = normalize(trit_L);
    }

#ifdef SPARKLE
    vec3 R = reflect(refractedLight, specNormal);
#else
    vec3 R = reflect(refractedLight, nNorm);
#endif

    float spec = max(0.0, dot(vNorm, R));

#ifndef HDR
    vec3 finalSpecular = trit_lightColor * min(1.0, pow(spec, trit_shininess + horizDist * SPECULAR_DISTANCE_FACTOR) * trit_sunIntensity * SPECULAR_BOOST * reflectivity);
#else
    vec3 finalSpecular = trit_lightColor * pow(spec, trit_shininess + horizDist * SPECULAR_DISTANCE_FACTOR) * trit_sunIntensity * SPECULAR_BOOST * reflectivity;
#endif

    // Allow lighting overrides in the user-functions.glsl
    user_lighting(trit_L, V, nNorm
                  , vVertex_Projection_Space, finalAmbient, finalDiffuse, finalSpecular);

    float shadow = user_cloud_shadow_fragment();

    finalDiffuse *= vec3(shadow);

    finalSpecular *= vec3(shadow);

    vec3 Csunlight = finalSpecular;

#ifndef HDR
    vec3 Clight = min(finalAmbient + finalDiffuse, 1.0);
#else
    vec3 Clight = finalAmbient + finalDiffuse;
#endif

    vec3 Cskylight = mix(trit_refractColor * Clight, reflectedColor.rgb  * vec3(shadow), reflectivity);

#ifdef OPENGL32
    vec3 Clightfoam = texture(trit_lightFoamTex, foamTexCoords).xyz;
    Clightfoam += texture(trit_lightFoamTex, foamTexCoords * 1.7).xyz;
    Clightfoam += texture(trit_lightFoamTex, foamTexCoords * 0.3).xyz;
    Clightfoam *= finalAmbient;
#else
    vec3 Clightfoam = texture2D(trit_lightFoamTex, foamTexCoords).xyz;
    Clightfoam += texture2D(trit_lightFoamTex, foamTexCoords * 1.7).xyz;
    Clightfoam += texture2D(trit_lightFoamTex, foamTexCoords * 0.3).xyz;
    Clightfoam *= finalAmbient;
#endif

    vec3 CiNoLight = vec3(0,0,0);

    // Fade out foam with distance to hide tiling
#ifdef BREAKING_WAVES
    float foamAmount = (clamp(finalSlopesAndFoam.w, 0.0, 1.0) * breakerFade);
    foamAmount = foamAmount * foamAmount;
    vec3 foamColor = Clightfoam * foamAmount;


#ifdef OPENGL32
    vec3 breakerTex = texture(trit_breakerTex, breakerTexCoords).xyz;
#else
    vec3 breakerTex = texture2D(trit_breakerTex, breakerTexCoords).xyz;
#endif

    float breakerNoise = max(0.0, (1.0 - abs(unscaledNoise.x * 6.0)));
    CiNoLight += breakerTex * breaker * tileFadeHoriz * breakerNoise;
#else
    float foamAmount = (clamp(finalSlopesAndFoam.w, 0.0, 1.0));
    foamAmount = foamAmount * foamAmount;
    vec3 foamColor = Clightfoam * foamAmount;
#endif

    CiNoLight += (foamColor * tileFadeHoriz * trit_foamBlend);
    CiNoLight += Clightfoam * wakeSlopeAndFoam.z * trit_foamBlend;

    vec3 Cwash = vec3(0,0,0);

#ifdef PROPELLER_WASH

#ifdef PER_FRAGMENT_PROP_WASH
    Cwash = applyPropWash(propWashCoord, finalAmbient);
#else
#ifdef OPENGL32
    Cwash = texture(trit_washTex, washTexCoords.xy).xyz * finalAmbient * washTexCoords.z;
#else
    Cwash = texture2D(trit_washTex, washTexCoords.xy).xyz * finalAmbient * washTexCoords.z;
#endif
#endif

    CiNoLight += Cwash * vec3(shadow);
#endif

    float doubleRefraction = max(0,dot(-vNorm,nNorm)) * (1.0 - dot(-vNorm, trit_invBasis[2]));
    doubleRefraction += finalSlopesAndFoam.w * BUBBLES;
    doubleRefraction *= tileFade;
    vec3 Ci = Cskylight + Csunlight + CiNoLight;
    Ci += trit_doubleRefractionColor * Clight * doubleRefraction * trit_doubleRefractionIntensity;

    float transparencyLocal = clamp(transparency, 0.0, 1.0);
    float alpha = hasHeightMap ? 1.0 - transparencyLocal : mix(1.0 - transparencyLocal, 1.0, reflectivity);
    vec4 waterColor = vec4(Ci, alpha);
    vec4 fogColor4 = vec4(trit_fogColor, hasHeightMap ? alpha : 1.0);

    float fogBlend = clamp(fogFactor, 0.0, 1.0);

    // Allow user override of fog in user-functions.glsl
    user_fog(V, waterColor, fogColor4, fogBlend);

    vec4 finalColor = mix(fogColor4, waterColor, fogBlend);

    finalColor.xyz = pow(finalColor.xyz, vec3(trit_oneOverGamma, trit_oneOverGamma, trit_oneOverGamma));

#ifndef HDR
    vec4 toneMappedColor = clamp(finalColor, 0.0, 1.0);
#else
    vec4 toneMappedColor = finalColor;
#endif

    user_tonemap(finalColor, toneMappedColor);

    toneMappedColor.w *= trit_transparency;

    vec3 Cdiffuse = vec3(0,0,0);
    user_diffuse_color( Cdiffuse, CiNoLight, reflectedColor, reflectivity );

    writeFragmentData(toneMappedColor, vec4( Cdiffuse, alpha ), trit_lightColor, nNorm);

}
