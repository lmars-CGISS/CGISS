#if GL_ES
	precision highp float;
#endif

uniform vec4 visibleAreaColor;
uniform vec4 hiddenAreaColor;
uniform mat4 inverse_projection_matrix;

//深度纹理
uniform sampler2D texture0;
//shadow Map
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;

// shadow Map的矩阵
uniform mat4 renderTextureMatrix1;
uniform mat4 renderTextureMatrix2;
uniform mat4 renderTextureMatrix3;
uniform mat4 renderTextureMatrix4;
uniform mat4 renderTextureMatrix5;
uniform mat4 renderTextureMatrix6;
uniform mat4 renderTextureMatrix7;

// 多个可视域的最大可见距离
uniform float farDist1;
uniform float farDist2;
uniform float farDist3;
uniform float farDist4;
uniform float farDist5;
uniform float farDist6;
uniform float farDist7;

// 多个可视域的观察点的视觉坐标
uniform vec3 viewPos1;
uniform vec3 viewPos2;
uniform vec3 viewPos3;
uniform vec3 viewPos4;
uniform vec3 viewPos5;
uniform vec3 viewPos6;
uniform vec3 viewPos7;

//纹理的层数
uniform int textureCount;

varying vec4 clip_pos;

#include <lib/ViewShed3D.glsllib>

float isVisibleForOneViewShed(in sampler2D viewShedTexture, in vec4 viewPos, in mat4 viewShedTextureMatrix, in float farDist, in vec3 viewShedPos)
{
	// 如果不在可视域的可视距离内就认为不可见
	float dis = length(viewPos.xyz - viewShedPos.xyz);
	if(dis > farDist)
	{
		return 1.0;
	}

	vec4 renderTextureCoord = viewShedTextureMatrix * viewPos;
	vec4 texCoord = renderTextureCoord / renderTextureCoord.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	texCoord.y = 1.0 - texCoord.y;

	// 如果不在可视域的纹理范围内认为不可见
	if (texCoord.x<0.0 || texCoord.x>1.0
		|| texCoord.y<0.0 || texCoord.y>1.0)
	{
		return 1.0;
	}
	
	float depth = getDepthFromShadowMap(viewShedTexture, texCoord);

	// 边界模糊效果没有处理，后期再做

	float dxc = abs(dFdx(texCoord.z));
	float dyc = abs(dFdy(texCoord.z));
	float dF = max(dxc, dyc);
	float bias = 1.0e-6 + dF;
	float c = float(depth+bias < texCoord.z);
	return c;
}

float isVisibleForMultiViewShed(in vec4 viewPos)
{
	float c = isVisibleForOneViewShed(texture1, viewPos, renderTextureMatrix1, farDist1, viewPos1);
	if(c == 0.0 || textureCount == 1)
	{
		return c;
	}
	c = isVisibleForOneViewShed(texture2, viewPos, renderTextureMatrix2, farDist2, viewPos2);
	if(c == 0.0 || textureCount == 2)
	{
		return c;
	}
	c = isVisibleForOneViewShed(texture3, viewPos, renderTextureMatrix3, farDist3, viewPos3);
	if(c == 0.0 || textureCount == 3)
	{
		return c;
	}
	c = isVisibleForOneViewShed(texture4, viewPos, renderTextureMatrix4, farDist4, viewPos4);
	if(c == 0.0 || textureCount == 4)
	{
		return c;
	}
	c = isVisibleForOneViewShed(texture5, viewPos, renderTextureMatrix5, farDist5, viewPos5);
	if(c == 0.0 || textureCount == 5)
	{
		return c;
	}
	c = isVisibleForOneViewShed(texture6, viewPos, renderTextureMatrix6, farDist6, viewPos6);
	if(c == 0.0 || textureCount == 6)
	{
		return c;
	}
	c = isVisibleForOneViewShed(texture7, viewPos, renderTextureMatrix7, farDist7, viewPos7);
	if(c == 0.0 || textureCount == 7)
	{
		return c;
	}
	return c;
}

void main()
{
	// 计算在主场景深度纹理上的坐标
	vec4 depthTexCoord = clip_pos / clip_pos.w;
	depthTexCoord.xy = depthTexCoord.xy * 0.5 + 0.5;
	depthTexCoord.y = 1.0 - depthTexCoord.y;
#if FLOAT_TEXTURE
	float depthValue = texture2D(texture0, depthTexCoord.xy).x;
#else
	float depthValue = unpackDepth(texture2D(texture0, depthTexCoord.xy));
#endif

	// 将当前片元的坐标变换到场景表面上
	vec4 pos = clip_pos;
	pos.z = depthValue * pos.w;

	vec4 viewPos = inverse_projection_matrix * pos;
	viewPos = viewPos / viewPos.w; 
	float c = isVisibleForMultiViewShed(viewPos);

	vec4 resultColor = mix(visibleAreaColor, hiddenAreaColor, vec4(c));
	gl_FragColor = resultColor;
}