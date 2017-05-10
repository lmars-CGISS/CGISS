#ifdef OPENGL32
in vec3 initialPosition;
in vec3 initialVelocity;
in float size;
in float startTime;
in float offsetX;
in float offsetY;
in float texCoordX;
in float texCoordY;
out float elapsed;
out vec2 texCoord;
out vec3 vEye;
out vec3 vWorld;
out float fogFactor;
#else
attribute vec3 initialPosition;
attribute vec3 initialVelocity;
attribute float size;
attribute float startTime;
attribute float offsetX;
attribute float offsetY;
attribute float texCoordX;
attribute float texCoordY;
varying float elapsed;
varying vec2 texCoord;
varying vec3 vEye;
varying vec3 vWorld;
varying float fogFactor;
#endif

uniform mat4 trit_mvProj;
uniform mat4 trit_modelView;
uniform float trit_time;
uniform vec3 trit_g;
uniform vec3 trit_cameraPos;
uniform vec3 trit_refOffset;

uniform bool trit_hasHeightMap;
uniform bool trit_hasUserHeightMap;
uniform vec2 trit_heightMapRangeOffset;
uniform mat4 trit_heightMapMatrix;
uniform sampler2D trit_heightMap;
uniform float trit_invSizeFactor;
uniform float trit_seaLevel;
uniform float trit_fogDensity;

vec4 overridePosition(in vec4 position);
float user_get_depth( in vec3 worldPos );

float getDepthFromHeightmap(in vec3 worldPos)
{
    float depth = 1000.0;

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

    return depth;
}


float getDepthFromBoundarymap(in vec4 localPos)
{
	float depth = 1000.0;
	vec4 clipPos = trit_mvProj * trit_modelView * localPos;
	vec3 ndcPos = clipPos.xyz / clipPos.w;
	ndcPos.xy = ndcPos.xy * 0.5 + 0.5;
	ndcPos.y = 1.0 - ndcPos.y;
	vec2 texCoord = ndcPos.xy;
	vec4 polyColor = texture2D(trit_heightMap, texCoord);
	if(polyColor.r > 0.8 && polyColor.g < 0.2 && polyColor.b < 0.2)
	{
		depth = -8000.0;
	}
	return depth;
}


void main()
{
    elapsed = trit_time - startTime;

    // p(t) = p0 + v0t + 0.5gt^2
    vec3 relPos = 0.5 * trit_g * elapsed * elapsed + initialVelocity * elapsed + initialPosition;
    vec2 offset = vec2(offsetX, offsetY);

    vec3 worldPos = relPos + trit_cameraPos - trit_refOffset;

    float depthFade = 1.0;

    vec4 wPos = vec4(relPos - trit_refOffset, 1.0);

	float depth = getDepthFromBoundarymap(wPos);
	if(depth < 0.0)
	{
		gl_Position = vec4(0.0,0.0,100.0,0.0);
		return;
	}

    vec4 eyeSpacePos = trit_modelView * wPos;

#ifdef POINT_SPRITES
    float dist = length(eyeSpacePos.xyz);
    gl_PointSize = max(1.0, size / dist);
#endif

    eyeSpacePos.xy += offset;

    wPos = eyeSpacePos * trit_modelView;

    texCoord = vec2(texCoordX, texCoordY);

    gl_Position = overridePosition(trit_mvProj * wPos);

    vEye = eyeSpacePos.xyz / eyeSpacePos.w;

    float fogExponent = length(vEye.xyz) * trit_fogDensity;
    fogFactor = clamp(exp(-(fogExponent * fogExponent)), 0.0, 1.0);

    vWorld = worldPos;
}
