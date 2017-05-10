#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

// 传入纹理
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

// 传入纹理边界
uniform vec4 texture0Bound;
uniform vec4 texture1Bound;
uniform vec4 texture2Bound;
uniform vec4 texture3Bound;

uniform float transparent;		// 地表透明值

varying vec4 globalBound;	// 全球纹理边界
varying vec2 texCoord;

// 判断点是否在矩形内
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}

bool isPointInRegionExt(vec2 point, vec4 region)
{
	if (region.x > region.z)
	{
		// 跨越全球边界的情况
		vec4 region0 = vec4(region.x, region.y, globalBound.z, region.w);
		vec4 region1 = vec4(globalBound.x, region.y, region.z, region.w);

		if (isPointInRegion(point, region0) || isPointInRegion(point, region1))
		{
			return true;
		}
	}
	else if (isPointInRegion(point, region))
	{
		return true;
	}

	return false;
}

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	vec4 color = vec4(0.0);
	
	// 根据 Mipmap 图层和 bound 取纹理
	if (isPointInRegionExt(texCoord, texture3Bound))
	{
		color = texture2D(texture3, gl_TexCoord[3].xy);
	}
	else if (isPointInRegionExt(texCoord, texture2Bound))
	{
		color = texture2D(texture2, gl_TexCoord[2].xy);
	}
	else if (isPointInRegionExt(texCoord, texture1Bound))
	{
		color = texture2D(texture1, gl_TexCoord[1].xy);
	}
	else if (isPointInRegionExt(texCoord, texture0Bound))
	{
		color = texture2D(texture0, gl_TexCoord[0].xy);
	}
	else
	{
		discard;
	}
	
#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	color.a = transparent;
	gl_FragColor = color;
}
