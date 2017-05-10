#if GL_ES
	precision highp float;
#endif

uniform mat4 renderTextureMatrix1;
uniform mat4 renderTextureMatrix2;
uniform mat4 renderTextureMatrix3;
uniform vec4 texture0_size;

uniform int isFloatTex;

//场景深度纹理
uniform sampler2D texture0;
//光源shadow Map
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

varying vec4 clip_pos;
varying float fWindowZ;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

bool isTexCoordValid(vec4 texCoord)
{
	return texCoord.x <= 1.0 && texCoord.x >= 0.0 && texCoord.y <= 1.0 && texCoord.y >= 0.0 && texCoord.z <= 1.0 && texCoord.z >= -1.0;
}

vec4 oomputeShadowTexCoord(const in vec4 posProjection, const mat4 renderTextureMatrix)
{
	vec4 renderTextureCoord = renderTextureMatrix * posProjection;
	vec4 texCoord = renderTextureCoord / renderTextureCoord.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	texCoord.y = 1.0 - texCoord.y;
	return texCoord;
}

float getDepthFromShadowMap(in sampler2D shadowMap, in vec4 uv)
{
	float shadowShade = 0.9;
	shadowShade = clamp(shadowShade, 0.4, 1.0);
	// 获取纹理中存储的深度值(从邻近的四个像素中取最大的深度)
	
	vec2 invShadowMapSize = vec2(1.0/texture0_size.x, 1.0/texture0_size.y);
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
	
	float shadow = max(max(depthLB, depthRB), max(depthLT, depthRT));
	float dxc = abs(dFdx(uv.z));
	float dyc = abs(dFdy(uv.z));
	float dF = max(dxc, dyc);
	float bias = 1.0e-6 + dF;
	if (shadow < 1.0 && shadow < uv.z)
	{
		if (depthLB < 1.0 && depthLB + bias < uv.z) shadeLB = shadowShade;
		if (depthRB < 1.0 && depthRB + bias < uv.z) shadeRB = shadowShade;
		if (depthLT < 1.0 && depthLT + bias < uv.z) shadeLT = shadowShade;
		if (depthRT < 1.0 && depthRT + bias < uv.z) shadeRT = shadowShade;
	}
	shadow = (shadeLB+shadeRB+shadeLT+shadeRT) / 4.0;

	return shadow;
}

float computeDepthLightSpace(const in vec4 posProjection)
{
	float depth = 1.0;
	
	// 计算shadowmap的UV纹理坐标
	
	vec4 texCoord = oomputeShadowTexCoord(posProjection, renderTextureMatrix1);
	if(isTexCoordValid(texCoord))
	{
		depth = getDepthFromShadowMap(texture1, texCoord);
		return depth;
	}
	
	texCoord = oomputeShadowTexCoord(posProjection, renderTextureMatrix2);
	if(isTexCoordValid(texCoord))
	{
		depth = getDepthFromShadowMap(texture2, texCoord);
		return depth;
	}
	
	texCoord = oomputeShadowTexCoord(posProjection, renderTextureMatrix3);
	if(isTexCoordValid(texCoord))
	{
		depth = getDepthFromShadowMap(texture3, texCoord);
		return depth;
	}
	
	return depth;
}

void main()
{	
	// 计算在主场景深度纹理上的坐标
	vec4 depthTexCoord = clip_pos / clip_pos.w;
	depthTexCoord.xy = depthTexCoord.xy * 0.5 + 0.5;
	depthTexCoord.y = 1.0 - depthTexCoord.y;
	float depthValue = texture2D(texture0, depthTexCoord.xy).x;

	// 将当前片元的坐标变换到场景表面上
	vec4 pos = clip_pos;
	pos.z = depthValue * pos.w;
	
	//计算顶点在光源空间内的深度值
	float depth = computeDepthLightSpace(pos);
	gl_FragColor = vec4(depth,depth,depth,1.0);
}