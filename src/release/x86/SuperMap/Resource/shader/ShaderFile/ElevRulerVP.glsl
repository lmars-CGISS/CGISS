
uniform mat4 texture0Matrix;
uniform mat4 texture1Matrix;
uniform mat4 texture2Matrix;
uniform mat4 texture3Matrix;

// 传入纹理边界
uniform vec4 elev1Bound;
uniform vec4 elev2Bound;
uniform vec4 elev3Bound;
uniform vec4 globalBoundary;	// 全球纹理边界
uniform float fTopLev; //最粗糙层层号

uniform float fEyeTexcoordHighX;
uniform float fEyeTexcoordHighY;
uniform float fEyeTexcoordLowX;
uniform float fEyeTexcoordLowY;

varying vec2 elevationTexCoord;

const float fOffset = 0.0009765625;

// 判断点是否在矩形内
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x&& point.x<region.z
		&& point.y<region.y&& point.y>region.w);
}

bool isPointInRegionExt(vec2 point, vec4 region)
{
	if (region.x > region.z)
	{
		// 跨越全球边界的情况
		vec4 region0 = vec4(region.x, region.y, globalBoundary.z, region.w);
		vec4 region1 = vec4(globalBoundary.x, region.y, region.z, region.w);

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

//计算用来在地形纹理上采样的纹理坐标
//relTexCoord 相对视点的纹理坐标 
vec2 CalculateElevationTexCoord(vec2 relTexCoord)
{
	vec2 elevTexCoord = vec2(0.0);
	float fLev = 0.0;
	
	//逐层判断顶点能落到的最精细tile层是哪层
	if (isPointInRegionExt(relTexCoord, elev3Bound))
	{
		fLev = 3;
		elevTexCoord = gl_TexCoord[3].xy;
	}
	else if (isPointInRegionExt(relTexCoord, elev2Bound))
	{
		fLev = 2;
		elevTexCoord = gl_TexCoord[2].xy;
	}
	else if (isPointInRegionExt(relTexCoord, elev1Bound))
	{
		fLev = 1;
		elevTexCoord = gl_TexCoord[1].xy;
	}
	else
	{
		fLev = 0;
		elevTexCoord = gl_TexCoord[0].xy;
	}
	
	float modLev = mod(fTopLev + fLev, 4.0);
	//根据层号模4的值确定在地形大纹理上的位置
	elevTexCoord = fract(elevTexCoord);
	elevTexCoord = clamp(elevTexCoord, 0.0 + fOffset, 1.0 - fOffset);
	elevTexCoord *= 0.5;
	elevTexCoord.x += 0.5 * mod(modLev, 2.0);
	float fModLev = modLev;
	elevTexCoord.y += 0.5 * step(1.1, fModLev);
	
	return elevTexCoord;
}

vec2 CalculateTexCoord()
{
	vec2 texCoordHigh = gl_MultiTexCoord0.xy;
	vec2 texCoordLow = gl_MultiTexCoord0.zw;
	vec2 eyeTexCoordLow = vec2(fEyeTexcoordLowX, fEyeTexcoordLowY);
	vec2 eyeTexCoordHigh = vec2(fEyeTexcoordHighX, fEyeTexcoordHighY);

	vec2 t1 = texCoordLow - eyeTexCoordLow;
	vec2 e = t1 - texCoordLow;
	vec2 t2 = ((-eyeTexCoordLow - e) + (texCoordLow - (t1 - e))) + texCoordHigh - eyeTexCoordHigh;
	vec2 highDifference = t1 + t2;
	vec2 lowDifference = t2 - (highDifference - t1);

	return (highDifference + lowDifference);
}

void main()
{
	// 纹理坐标变换
	vec4 texCoord0 = vec4(CalculateTexCoord(),0.0,1.0);
	gl_TexCoord[0].xy = (texture0Matrix * texCoord0).xy;
	gl_TexCoord[1].xy = (texture1Matrix * texCoord0).xy;
	gl_TexCoord[2].xy = (texture2Matrix * texCoord0).xy;
	gl_TexCoord[3].xy = (texture3Matrix * texCoord0).xy;
	
	//计算顶点在地形纹理中的纹理坐标
	elevationTexCoord = CalculateElevationTexCoord(texCoord0.xy);

	// 顶点坐标变换
	gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);
}
