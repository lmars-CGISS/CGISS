
uniform sampler2D shadowMap0;
uniform sampler2D shadowMap1;
uniform sampler2D shadowMap2;

uniform vec4 inverseShadowmapSize0;
uniform vec4 inverseShadowmapSize1;
uniform vec4 inverseShadowmapSize2;

uniform vec4 pssmSplitPoints;
uniform vec4 shadowColor;
uniform int isFloatTex;

varying vec4 shadowmapTexCoord0;
varying vec4 shadowmapTexCoord1;
varying vec4 shadowmapTexCoord2;
varying float cameraDepth;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

float calcDepthShadow(sampler2D shadowMap, vec4 uv, vec4 invShadowMapSize)
{
	// 把shadowColor的范围从 [0.0,1.0] 变换到 [1.0,0.4]
	float shadowShade = 1.0 - shadowColor.x;
	shadowShade = clamp(shadowShade, 0.4, 1.0);

	uv /= uv.w;
	vec3 halfTexelSize = 0.5 * vec3(invShadowMapSize.xy, -invShadowMapSize.x);
	
	float shadeLB = 1.0, shadeRB = 1.0, shadeLT = 1.0, shadeRT = 1.0;
	// 左下
	vec4 depthLBColor = texture2D(shadowMap, uv.xy-halfTexelSize.xy);
	// 右下
	vec4 depthRBColor = texture2D(shadowMap, uv.xy-halfTexelSize.zy);
	// 左上
	vec4 depthLTColor = texture2D(shadowMap, uv.xy+halfTexelSize.zy);
	// 右上
	vec4 depthRTColor = texture2D(shadowMap, uv.xy+halfTexelSize.xy);

	float depthLB = depthLBColor.r;
	float depthRB = depthRBColor.r;
	float depthLT = depthLTColor.r;
	float depthRT = depthRTColor.r;
	if (isFloatTex != 1)
	{
		depthLB = unpackDepth(depthLBColor);
		depthLB = depthLB * 2.0 - 1.0;
		depthRB = unpackDepth(depthRBColor);
		depthRB = depthRB * 2.0 - 1.0;
		depthLT = unpackDepth(depthLTColor);
		depthLT = depthLT * 2.0 - 1.0;
		depthRT = unpackDepth(depthRTColor);
		depthRT = depthRT * 2.0 - 1.0;
	}
	
	if (depthLB < 1.0 && depthLB < uv.z) shadeLB = shadowShade;
	if (depthRB < 1.0 && depthRB < uv.z) shadeRB = shadowShade;
	if (depthLT < 1.0 && depthLT < uv.z) shadeLT = shadowShade;
	if (depthRT < 1.0 && depthRT < uv.z) shadeRT = shadowShade;
	
	// 双线性插值(效果不对，暂时注释掉)
	//vec2 texelPos = uv.xy / invShadowMapSize.xy;
	////vec2 offset = texelPos - floor(texelPos);
	//vec2 offset = texelPos - (floor(texelPos-0.5)+0.5);
	//float shadow = (1.0-offset.x)*(1.0-offset.y)*shadeLB + offset.x*(1.0-offset.y)*shadeRB
	//	+ (1.0-offset.x)*offset.y*shadeLT + offset.x*offset.y*shadeRT;
	
	// 取平均值(4-sample PCF)
	float shadow = (shadeLB+shadeRB+shadeLT+shadeRT) / 4.0;

	return shadow;
}

float calcPSSMDepthShadow()
{
	float shadow = 1.0;
	// calculate shadow
	if (cameraDepth <= pssmSplitPoints.y)
	{
		shadow = calcDepthShadow(shadowMap0, shadowmapTexCoord0, inverseShadowmapSize0);
	}
	else if (cameraDepth <= pssmSplitPoints.z)
	{
		shadow = calcDepthShadow(shadowMap1, shadowmapTexCoord1, inverseShadowmapSize1);
	}
	else
	{
		shadow = calcDepthShadow(shadowMap2, shadowmapTexCoord2, inverseShadowmapSize2);
	}

	return shadow;
}

void main()
{
	float shadow = calcPSSMDepthShadow();
	
	if (shadow >= 1.0)
	{
		discard;
	}

    gl_FragColor = vec4(shadow, shadow, shadow, 1.0);
}
