#define PRECISION_GUARD 2.0

#ifdef OPENGL32
in vec2 vertex;
out vec3 V;
out vec2 foamTexCoords;
out vec2 texCoords;
out vec2 noiseTexCoords;
out vec3 wakeSlopeAndFoam;
#ifdef PROPELLER_WASH
out vec3 washTexCoords;
#endif
out float fogFactor;
out float transparency;
out float depth;
#ifdef BREAKING_WAVES
out float breaker;
out float breakerFade;
out vec2 breakerTexCoords;
#endif
#ifdef LEEWARD_DAMPENING
out float leewardDampening;
#endif
out vec4 vVertex_Eye_Space;
out vec4 vVertex_Projection_Space;
#ifdef PER_FRAGMENT_PROP_WASH
out vec3 propWashCoord;
#endif
#else
varying vec3 V;
varying vec2 foamTexCoords;
varying vec2 texCoords;
varying vec2 noiseTexCoords;
varying vec3 wakeSlopeAndFoam;
#ifdef PROPELLER_WASH
varying vec3 washTexCoords;
#endif
varying float fogFactor;
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

uniform float trit_foamScale;
uniform float trit_depthOffset;
uniform mat4 trit_invModelviewProj;
uniform mat4 trit_modelview;
uniform mat4 trit_projection;
uniform vec4 trit_plane;
uniform mat3 trit_basis;
uniform mat3 trit_invBasis;
uniform vec3 trit_cameraPos;
uniform mat4 trit_gridScale;
uniform sampler2D trit_displacementMap;
uniform vec2 trit_textureSize;
uniform float trit_fogDensity;
uniform float trit_fogDensityBelow;
uniform float trit_invDampingDistance;
uniform vec3 trit_floorPlanePoint;
uniform vec3 trit_floorPlaneNormal;
uniform float trit_time;
uniform float trit_seaLevel;

uniform vec2 trit_zNearFar;

uniform bool trit_hasHeightMap;
uniform bool trit_hasUserHeightMap;
uniform sampler2D trit_heightMap;
uniform vec2 trit_heightMapRangeOffset;
uniform mat4 trit_heightMapMatrix;

uniform bool trit_hasDepthMap;
uniform sampler2D trit_depthMap;

#ifdef BREAKING_WAVES
uniform float trit_kexp;
uniform float trit_breakerWavelength;
uniform float trit_breakerWavelengthVariance;
uniform vec3 trit_breakerDirection;
uniform float trit_breakerAmplitude;
uniform float trit_breakerPhaseConstant;
uniform float trit_surgeDepth;
uniform float trit_steepnessVariance;
uniform float trit_breakerDepthFalloff;
#ifdef BREAKING_WAVES_MAP
uniform sampler2D trit_breakingWaveMap;
uniform mat4 trit_breakingWaveMapMatrix;
uniform bool trit_hasBreakingWaveMap;
#endif
#endif

#ifdef LEEWARD_DAMPENING
uniform vec3 trit_windDir;
#endif

#define PI 3.14159265
#define TWOPI (2.0 * 3.14159265)

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

uniform sampler2D trit_displacementTexture;

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

void user_intercept(in vec3 worldPosition, in vec3 localPosition, in vec4 eyePosition, in vec4 projectedPosition);
vec4 overridePosition(in vec4 position);
float user_get_depth( in vec3 worldPos );

void getDepthFromHeightmap(in vec3 worldPos)
{
    vec2 texCoord = (trit_heightMapMatrix * vec4(worldPos, 1.0)).xy;
    if (clamp(texCoord, vec2(0.0, 0.0), vec2(1.0, 1.0)) == texCoord) {
#ifdef OPENGL32
        float height = texture(trit_heightMap, texCoord).x;
#else
        float height = texture2D(trit_heightMap, texCoord).x;
#endif
        height = height*trit_heightMapRangeOffset.x + trit_heightMapRangeOffset.y;
        depth = -(height - trit_seaLevel);
    }
}

void getDepthFromDepthmap(in vec3 localPos)
{
    vec4 clipPos = trit_projection * (trit_modelview * vec4(localPos, 1.0));
    vec3 ndcPos = clipPos.xyz / clipPos.w;
    vec2 texCoord = ndcPos.xy * 0.5 + 0.5;
#ifdef OPENGL32
    float terrainZ = texture(trit_depthMap, texCoord).x;
#else
    float terrainZ = texture2D(trit_depthMap, texCoord).x;
#endif

    ndcPos.z = mix(trit_zNearFar.x, trit_zNearFar.y, terrainZ);

    clipPos.w = trit_projection[3][2] / (ndcPos.z - (trit_projection[2][2] / trit_projection[2][3]));
    clipPos.xyz = ndcPos * clipPos.w;

    vec4 terrainWorld = trit_invModelviewProj * clipPos;

    depth = length(terrainWorld.xyz) - length(localPos);
}

void computeTransparency(in vec3 worldPos, in vec3 localPos)
{
    depth = DEFAULT_DEPTH;
    // Compute depth at this position
    if ( trit_hasUserHeightMap ) {
        depth = user_get_depth(worldPos);
    } else if (trit_hasHeightMap) {
        getDepthFromHeightmap(worldPos);
    } else if (trit_hasDepthMap) {
        getDepthFromDepthmap(localPos);
    } else {
        vec3 up = trit_invBasis * vec3(0, 0, 1);
        vec3 l = -up;
        vec3 l0 = worldPos;
        vec3 n = trit_floorPlaneNormal;
        vec3 p0 = trit_floorPlanePoint;
        float numerator = dot((p0 - l0), n);
        float denominator = dot(l, n);
        if (denominator != 0.0) {
            depth = numerator / denominator;
        }
    }

    // Compute fog at this distance underwater
    float fogExponent = abs(depth) * trit_fogDensityBelow;
    transparency = clamp(exp(-abs(fogExponent)), 0.0, 1.0);
}

float applyBreakingWaves(in vec3 v, in float fade, in vec3 worldPos)
{
    float finalz = 0;

#ifdef BREAKING_WAVES
    breaker = 0.0;
    breakerTexCoords = vec2(0.0,1.0);

    bool hasHeightMap = (trit_hasHeightMap || trit_hasUserHeightMap);
    if (hasHeightMap && trit_breakerAmplitude > 0 && depth > 1.0 && depth < trit_breakerWavelength * 0.5) {

        vec3 direction = trit_breakerDirection;
        float alpha = 1.0;

#ifdef BREAKING_WAVES_MAP
        bool gotDirection = false;
        if (trit_hasBreakingWaveMap) {
            vec2 texCoord = (trit_breakingWaveMapMatrix * vec4(worldPos, 1.0)).xy;
            if (clamp(texCoord, vec2(0.0, 0.0), vec2(1.0, 1.0)) == texCoord) {
#ifdef OPENGL32
                vec4 t = texture(trit_breakingWaveMap, texCoord);
#else
                vec4 t = texture2D(trit_breakingWaveMap, texCoord);
#endif

                vec3 d = t.xyz;
                alpha = t.w;

                if (dot(d,d) == 0) {
                    direction = normalize(d);
                    gotDirection = true;
                }
            }
        }
        if (!gotDirection) return 0;
#endif

        float halfWavelength = trit_breakerWavelength * 0.5;
        float scaleFactor = ((depth - halfWavelength) / halfWavelength);
        float wavelength = trit_breakerWavelength + scaleFactor * trit_breakerWavelengthVariance;

        float halfKexp = trit_kexp * 0.5;
        scaleFactor = (depth - halfKexp) / halfKexp;
        scaleFactor *= 1.0 + trit_steepnessVariance;
        float k = (trit_kexp + scaleFactor) * (1.0 - fade);

        vec3 localDir = trit_basis * direction;
        localDir.z = 0;
        localDir = normalize(localDir);
        float dotResult = dot(-localDir.xy, v.xy) * TWOPI / wavelength;

        finalz = (dotResult + trit_breakerPhaseConstant * trit_time);

        vec3 binormal = cross(vec3(0.0, 0.0, 1.0), localDir);
        breakerTexCoords.x = dot(binormal.xy, v.xy);
        breakerTexCoords.x /= trit_foamScale * 8.0;

#define OFFSET (PI * 0.3)
        float y = mod(finalz, TWOPI);
        if (y < OFFSET) return 0;
        float num = PI - y;
        float den = PI - OFFSET;
        breakerTexCoords.y = num / den;
        float sinz = sin(finalz);

        finalz = (sinz + 1.0) * 0.5;

        finalz = trit_breakerAmplitude * pow(finalz, max(1.0, k));

        finalz *= 1.0 - min(depth * trit_breakerDepthFalloff / halfWavelength, 1.0);
        finalz *= alpha;
        finalz = max(0, finalz);

        breaker = clamp(sinz, 0.0, 1.0);

        breaker *= 1.0 - min((depth * 3.0 * trit_breakerDepthFalloff) / halfWavelength, 1.0);
        breaker *= alpha;

        // Hide the backs of waves if we're transparent
        float opacity = 1.0 - transparency;
        finalz = mix(0.0, finalz, pow(opacity, 6.0));
    }
#endif

    return finalz;
}

float applyCircularWaves(in vec3 v, float fade)
{
    int i;

    float dispZ = 0;

    vec2 slope = vec2(0.0, 0.0);
    float disp = 0.0;

    for (i = 0; i < trit_numCircularWaves; i++) {

        vec2 D = (v - trit_circularWaves[i].position).xy;
        float dist = length(D);

        float r = dist - trit_circularWaves[i].radius;
        if (abs(r) < trit_circularWaves[i].halfWavelength) {

            float amplitude = trit_circularWaves[i].amplitude;

            float theta = trit_circularWaves[i].k * r;
            disp += amplitude * cos(theta);
            float derivative = amplitude * -sin(theta);
            slope +=  D * (derivative / dist);
        }
    }

    dispZ += disp * fade;

    wakeSlopeAndFoam.z += max(0.0, dispZ);
    wakeSlopeAndFoam.xy += slope * fade;

    return dispZ;
}

void applyLeewardDampening(in vec3 v)
{
#ifdef LEEWARD_DAMPENING
    int i;

    float maxDampening = 0;

    for (i = 0; i < trit_numLeewardDampeners; i++) {
        vec3 bowPos = trit_leewardDampeners[i].bowPos;
        vec3 sternPos = trit_leewardDampeners[i].sternPos;
        vec3 center = (bowPos + sternPos) * 0.5;
        vec3 P = v - center;
        vec3 axis = normalize(bowPos - sternPos);
        float radius = length(bowPos - sternPos) * 0.5;

        float blockage = 1.0 - abs(dot(axis, trit_windDir));
        float directional = max(dot(P, trit_windDir), 0);
        float distance = max(1.0 - length(P) / radius, 0);

        float dampening = blockage * directional * distance * trit_leewardDampeningStrength;
        dampening *= trit_leewardDampeners[i].velocityDampening;
        maxDampening = max(dampening, maxDampening);
    }

    leewardDampening = 1.0 - maxDampening;
    leewardDampening = clamp(leewardDampening, 0, 1.0);
#endif
}

float applyKelvinWakes(in vec3 v, float fade)
{
    float displacementZ = 0;

#ifdef KELVIN_WAKES
    vec2 slope = vec2(0.0, 0.0);
    float foam = 0;

    int i;
    for (i = 0; i < trit_numKelvinWakes; i++) {

        vec3 X0 = trit_wakes[i].position - trit_wakes[i].shipPosition;
        vec3 T = normalize(X0);
        vec3 N = vec3(0,0,1);
        vec3 B = normalize(cross(N, T));

        vec3 P = v - trit_wakes[i].shipPosition;
        vec3 X;
        X.x = dot(P.xy, T.xy);
        X.y = dot(P.xy, B.xy);

        float xLen = length(X0);
        vec2 tc;
        tc.x = X.x / (1.54 * xLen);
        tc.y = (X.y) / (1.54 * xLen) + 0.5;

        if (clamp(tc, 0.01, 0.99) == tc) {
#ifdef OPENGL32
            vec4 sample = texture(trit_displacementTexture, tc);
#else
            vec4 sample = texture2D(trit_displacementTexture, tc);
#endif
            float displacement = sample.w;

            displacement *= trit_wakes[i].amplitude * fade;

            vec3 normal = normalize(sample.xyz * 2.0 - 1.0);
            float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
            mat3 TBN = mat3( T * invmax, B * invmax, N );

            normal = TBN * normal;

            if (clamp(normal.xy, vec2(-0.05, -0.05), vec2(0.05, 0.05)) == normal.xy) {
                normal = vec3(0,0,1);
            }

            normal.xy *= min(1.0, trit_wakes[i].amplitude);
            normal = normalize(normal);

            displacementZ = max(displacementZ, displacement);

            vec2 s = vec2(normal.x / normal.z, normal.y / normal.z);
            slope = max(slope, s);
            foam += length(s) * trit_wakes[i].foamAmount;
        }
    }

    wakeSlopeAndFoam.z += min(1.0, foam);
    wakeSlopeAndFoam.xy += slope * fade;
#endif

    return displacementZ;
}

void applyPropWash(in vec3 v)
{
#ifdef PROPELLER_WASH

    washTexCoords = vec3(0.0, 0.0, 0.0);

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

            if (clamp(nd, 0.0, 3.0) == nd) {
                washTexCoords.x = nd;
                // The t0 parameter from our initial distance test to the line segment makes
                // for a handy t texture coordinate
                washTexCoords.y =  (trit_washes[i].washLength - distFromSource) / trit_washes[i].washWidth;

                // We stuff the blend factor into the r coordinate.

                //float blend = max(0.0, 1.0 - distFromSource / (trit_washLength));
                float blend = mix(trit_washes[i].alphaEnd, trit_washes[i].alphaStart, t0);
                blend *= max(0.0, 1.0 - nd * nd);
                washTexCoords.z = clamp(blend, 0.0, 1.0);
            }
        }
    }
#endif
}

void displace(in vec3 vWorld, inout vec3 vLocal)
{
    float fade = 1.0 - smoothstep(0.0, 1.0, length(vWorld - trit_cameraPos) * trit_invDampingDistance);

#ifdef BREAKING_WAVES
    // Fade out waves in the surge zone
    float depthFade = 1.0;

    if (trit_surgeDepth > 0) {
        depthFade = min(trit_surgeDepth, depth) / trit_surgeDepth;
        depthFade = clamp(depthFade, 0.0, 1.0);
    }

    fade *= depthFade;
    breakerFade = depthFade;
#endif

    // Transform so z is up
    vec3 localVWorld = trit_basis * vWorld;
    vec3 localVLocal = trit_basis * vLocal;

    texCoords = localVWorld.xy / trit_textureSize;

#ifdef OPENGL32
    vec3 displacement = texture(trit_displacementMap, texCoords).xyz;
#else
    vec3 displacement = texture2D(trit_displacementMap, texCoords).xyz;
#endif

    // Hide the backs of waves if we're transparent
    float opacity = 1.0 - transparency;
    displacement.z = mix(0.0, displacement.z, pow(opacity, 6.0));

    localVLocal.xy += displacement.xy * fade;

#if (defined(KELVIN_WAKES) || defined(PROPELLER_WASH))
    if (trit_doWakes) {
        wakeSlopeAndFoam.xyz = vec3(0.0, 0.0, 0.0);
        localVLocal.z += applyKelvinWakes(localVWorld, fade);
        localVLocal.z += applyCircularWaves(localVWorld, fade);
#ifdef PER_FRAGMENT_PROP_WASH
        propWashCoord = localVWorld;
#else
        applyPropWash(localVWorld);
#endif
        applyLeewardDampening(localVWorld);
    } else {
#ifdef PROPELLER_WASH
        washTexCoords = vec3(0.0, 0.0, 0.0);
#endif
    }
#endif

#ifdef LEEWARD_DAMPENING
    localVLocal.z += displacement.z * fade * leewardDampening;
#else
    localVLocal.z += displacement.z * fade;
#endif

    localVLocal.z += applyBreakingWaves(localVWorld, fade, vWorld);

    foamTexCoords = localVWorld.xy / trit_foamScale;
    noiseTexCoords = texCoords * 0.03;

    vLocal = trit_invBasis * localVLocal;
}

bool projectToSea(in vec4 v, out vec4 vLocal, out vec4 vWorld)
{
    // Get the line this screen position projects to
    vec4 p0 = v;
    vec4 p1 = v;
    p0.z = trit_zNearFar.x;
    p1.z = trit_zNearFar.y;

    // Transform into world coords
    p0 = trit_invModelviewProj * p0;
    p1 = trit_invModelviewProj * p1;

    // Intersect with the sea level
    vec3 up = trit_invBasis * vec3(0, 0, 1);
    vec4 p = trit_plane;

    float altitude = dot(trit_cameraPos, up) - trit_seaLevel;
    float offset = 0;

    if (clamp(altitude, 0, PRECISION_GUARD) == altitude) {
        p.w += PRECISION_GUARD;
        offset = PRECISION_GUARD;
    } else if (clamp(altitude, -PRECISION_GUARD, 0) == altitude) {
        p.w -= PRECISION_GUARD;
        offset = -PRECISION_GUARD;
    }

    vec4 dp = p1 - p0;
    float t = -dot(p0, p) / dot( dp, p);
    if (t > 0.0 && t < 1.0) {
        vLocal = dp * t + p0;
        vLocal /= vLocal.w;
        vLocal.xyz += up * offset;
        vWorld = vLocal + vec4(trit_cameraPos, 1.0);
        return true;
    } else {
        vLocal = vec4(0.0, 0.0, 0.0, 0.0);
        vWorld = vec4(0.0, 0.0, 0.0, 0.0);
        return false;
    }
}

void main()
{
    wakeSlopeAndFoam = vec3( 0. );
    transparency = 0.0;

#ifdef LEEWARD_DAMPENING
    leewardDampening = 1.0;
#endif

    vec4 worldPos, localPos;

#ifdef OPENGL32
    vec4 gridPos = trit_gridScale * vec4(vertex.x, vertex.y, 0.0, 1.0);
#else
    vec4 gridPos = trit_gridScale * gl_Vertex;
#endif

    if (projectToSea(gridPos, localPos, worldPos)) {
        computeTransparency(worldPos.xyz, localPos.xyz);

        // Displace
        displace(worldPos.xyz, localPos.xyz);

        V = localPos.xyz;

        // Project it back again, apply depth offset.
        vec4 v = trit_modelview * localPos;
        vVertex_Eye_Space = v;
        v.w -= trit_depthOffset;
        vec4 vVertInProjSpc = trit_projection * v;
        vVertex_Projection_Space = vVertInProjSpc;
        gl_Position = overridePosition(vVertInProjSpc);

        user_intercept(V + trit_cameraPos, V, vVertex_Eye_Space, vVertex_Projection_Space);
    } else {
        V = vec3(0.0, 0.0, 0.0);
        foamTexCoords = vec2(0.0, 0.0);
        texCoords = vec2(0.0, 0.0);
        noiseTexCoords = vec2(0.0, 0.0);
        wakeSlopeAndFoam = vec3(0.0, 0.0, 0.0);
#ifdef PROPELLER_WASH
        washTexCoords = vec3(0.0, 0.0, 0.0);
#endif
        fogFactor = 1.0;
        transparency = 0.0;
        vVertex_Eye_Space = vec4(0,0,0,1);
        vec4 vVertInProjSpc = vec4(gridPos.x, gridPos.y, 100.0, 1.0);
        vVertex_Projection_Space = vVertInProjSpc;
        gl_Position = vVertInProjSpc;
    }

    float fogExponent = length(V.xyz) * trit_fogDensity;
    fogFactor = clamp(exp(-(fogExponent * fogExponent)), 0.0, 1.0);
}