#ifdef OPENGL32
in vec4 position;
out vec3 intensity;
out vec3 view;
#else
attribute vec4 position;
varying vec3 intensity;
varying vec3 view;
#endif

uniform mat4 mvProj;
uniform vec3 origin;
uniform float spacing;
uniform vec3 extinction;
uniform vec3 sunDir;
uniform vec3 viewer;

uniform mat3 basis;
uniform mat3 invBasis;
uniform sampler2D displacementMap;
uniform sampler2D slopeFoamMap;
uniform vec2 textureSize;
uniform vec3 viewDir;
uniform float fade;

vec4 overridePosition(in vec4 position);

vec3 CalculateWaterNormal(inout vec3 v)
{
    vec3 localV = basis * v;
    vec2 texCoords = localV.xy / textureSize;

#ifdef OPENGL32
    vec3 slopesAndFoam = texture(slopeFoamMap, texCoords).xyz;
    vec3 displacement = texture(displacementMap, texCoords).xyz;
#else
    vec3 slopesAndFoam = texture2D(slopeFoamMap, texCoords).xyz;
    vec3 displacement = texture2D(displacementMap, texCoords).xyz;
#endif

    localV += displacement;

    v = invBasis * localV;

    vec3 sx = vec3(1.0, 0.0, slopesAndFoam.x);
    vec3 sy = vec3(0.0, 1.0, slopesAndFoam.y);

    vec3 nNorm = invBasis * normalize(cross(sx, sy));

    return nNorm;
}

float FastFresnel(vec3 I, vec3 N)
{
    const float R0 = 0.0204;
    return R0 + (1.0-R0) * pow(1 - dot(I, N), 5.0);
}

void main()
{
    vec3 worldPos = position.xyz * vec3(spacing, 1.0, spacing);
    worldPos += origin;

    vec3 normal = CalculateWaterNormal(worldPos);
    float vertDist = length(worldPos - viewer);
    float totalDist = position.w + vertDist;

    if (position.w > 0.0 ) {
        vec3 refr = refract(-sunDir, normal, 1.0/1.333);
        worldPos += refr * position.w;
        intensity = vec3(0.0,0.0,0.0);
    } else {
        float tr = 1.0 - FastFresnel(sunDir, normal);
        intensity = exp(-totalDist * extinction) * tr;
    }

    intensity *= fade;

    view = worldPos - viewer;

    vec4 clipPos = mvProj * vec4(worldPos, 1.0);
    clipPos.z = 0.01;

    gl_Position = overridePosition(clipPos);
}
