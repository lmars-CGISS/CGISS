#if GL_ES
	precision highp float;
#endif

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

uniform vec4 pssmSplitPoints;
uniform int renderingAssist;
uniform int isFloatTex;

varying vec4 shadowmapTexCoord0;
varying vec4 shadowmapTexCoord1;
varying vec4 shadowmapTexCoord2;
varying vec4 windowPos;
varying float cameraDepth;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

vec4 packIntToVec4i(float value)
{
	const vec4 bitShifts = vec4(1.0, 256.0, 256.0*256.0, 256.0*256.0*256.0);
	const vec4 c_bias = vec4(1.0/256.0, 1.0/256.0, 1.0/256.0, 1.0/256.0);

	vec4 color;
	color.w = floor(value/bitShifts.w);
	color.z = floor(value/bitShifts.z) - color.w*bitShifts.y;
	color.y = floor(value/bitShifts.y) - color.w*bitShifts.z - color.z*bitShifts.y;
	color.x = value - color.w*bitShifts.w - color.z*bitShifts.z -color.y*bitShifts.y;

	return color*c_bias;
}

float unpackIntFromVec4i(vec4 color)
{
	const vec4 bitShifts = vec4(1.0, 256.0, 256.0*256.0, 256.0*256.0*256.0);
	const vec4 c_bias = vec4(256.0, 256.0, 256.0, 256.0);
	return dot(color*c_bias, bitShifts);
}

float calcDepthShadow(sampler2D shadowMap, vec4 uv)
{
	uv /= uv.w;
	
	// 获取纹理中存储的深度值
	vec4 depthColor = texture2D(shadowMap, uv.xy);
	float depth = depthColor.x;
	if (isFloatTex != 1)
	{
		depth = unpackDepth(depthColor);
		depth = depth * 2.0 - 1.0;
	}

	float shadow = 1.0;
	if (depth < 1.0 && depth < uv.z) shadow = 0.0;
	
	return shadow;
}

float calcPSSMDepthShadow()
{
	float shadow = 1.0;
	// calculate shadow
	shadow = calcDepthShadow(texture2, shadowmapTexCoord2);

	return shadow;
}

void main()
{
	float shadow = calcPSSMDepthShadow();
	
	vec4 texCoord = windowPos / windowPos.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	// 直接从屏幕坐标变换到纹理坐标不需要颠倒y方向
	//texCoord.y = 1.0 - texCoord.y;
	
	vec4 color;
	if (renderingAssist == 1)
	{
		color = texture2D(texture3, texCoord.xy);
	}
	else
	{
		color = texture2D(texture4, texCoord.xy);
	}
	
	if (isFloatTex == 1)
	{
		color.r += shadow;
	}
	else
	{
		color = packIntToVec4i(unpackIntFromVec4i(color)+shadow);
	}

	gl_FragColor = color;
}
