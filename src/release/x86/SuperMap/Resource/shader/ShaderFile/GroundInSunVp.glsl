uniform mat4 texture0Matrix;
uniform mat4 texture1Matrix;
uniform mat4 texture2Matrix;
uniform mat4 texture3Matrix;

uniform mat4 elevTextureMatrix;
uniform mat4 coarseElevTextureMatrix;

// 传入纹理边界
uniform vec4 elevBound;
uniform vec4 coarseElevBound;

uniform int nTerrainLevel;

//融合
uniform float fMorphSpace;
uniform float fMaxDistance;

uniform vec4 globalBoundary;	// 全球纹理边界
uniform float fTopLev; //最粗糙层层号

uniform sampler2D elevationTexture;
uniform sampler2D elevationNormalTexture;

uniform sampler2D coarseElevationTexture;
uniform sampler2D coarseElevationNormalTexture;

uniform vec3 vEyePosHigh;
uniform vec3 vEyePosLow;

uniform float fPlanetRadius;

uniform float fEyeTexcoordHighX;
uniform float fEyeTexcoordHighY;
uniform float fEyeTexcoordLowX;
uniform float fEyeTexcoordLowY;

uniform float fEyeElevTexcoordHighX;
uniform float fEyeElevTexcoordHighY;
uniform float fEyeElevTexcoordLowX;
uniform float fEyeElevTexcoordLowY;

uniform mat4 modelMatrix;
uniform vec3 v3CameraPos;
uniform vec3 v3LightPos;
uniform vec3 v3InvWavelength;
uniform float fCameraHeight;
uniform float fCameraHeight2;
uniform float fOuterRadius;
uniform float fOuterRadius2;
uniform float fInnerRadius;
uniform float fInnerRadius2;
uniform float fKrESun;
uniform float fKmESun;
uniform float fKr4PI;
uniform float fKm4PI;
uniform float fScale;
uniform float fScaleDepth;
uniform float fScaleOverScaleDepth;
uniform vec3 v3StartupConsts;
uniform float terrainScale;
uniform float fFloatTexture;
uniform int hasTerrainData;


uniform vec4 ambient_light_colour;
uniform vec4 light_diffuse_colour;
uniform vec4 light_specular_colour;
uniform vec4 surface_ambient_colour;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;


varying vec2 texCoord;
varying vec4 globalBound;
varying vec3 realNormal;
varying vec3 vec3Rayleigh;		// Rayleigh 散射颜色

varying vec3 vec3AdjustedMie;		// Mie 散射颜色
varying float fFogFactor;		// 雾因子，值的范围（0，1）
varying vec3  vertNorm;
varying vec3 vLight;

varying vec4 mixColor;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

#if CLIP
varying vec4 clip_vertex;		// 用于裁剪
uniform mat4 worldview_matrix;
#endif

const int nSamples = 2;			// 采样数
const float fKSunColor = 3.0;
const vec4 v4SunsetAmbientAndFogDensity = vec4(0.1, 0.1, 0.1, 0.1);
const float fOffset = 0.001953125;

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

vec2 quickTwoSum(float a, float b)
{
	float s = a + b;
	float e = b - (s - a);
	return vec2(s, e);
}

vec2 twoSum(float a, float b)
{
	float s = a + b;
	float v = s - a;
	float e = (a - (s - v)) + (b - v);
	return vec2(s, e);
}

vec2 df64_Add(vec2 a, vec2 b)
{
	vec2 s, t;
	s = twoSum(a.x, b.x);
	t = twoSum(a.y, b.y);
	s.y += t.x;
	s = quickTwoSum(s.x, s.y);
	s.y += t.y;
	s = quickTwoSum(s.x, s.y);
	return s;
}

vec2 split(float a)
{
	float t = a * 4097.0;
	float a_hi = t - (t - a);
	float a_lo = a - a_hi;
	return vec2(a_hi, a_lo);
}

vec2 twoProd(float a, float b)
{
	float p = a * b;
	vec2 aS = split(a);
	vec2 bS = split(b);
	float err = ((aS.x * bS.x - p)
	             + aS.x * bS.y + aS.y * bS.x)
				 + aS.y * bS.y;
	return vec2(p, err);
}

vec2 df64_mult(vec2 a, vec2 b)
{
	vec2 p;

	p = twoProd(a.x, b.x);
	p.y += a.x * b.y;
	p.y += a.y * b.x;
	return p;
}

//将保存在RGBA通道中的四个byte还原为float
float Convert4ByteToFloat(vec4 vByte)
{
	//b,g,r,a通道分别保存了原始高度的四个byte，因此需要将其进行位移还原到原来的位，a通道存储高度值是否为负值，1为负值，0为正值
	//高度在CPU中扩大了一千倍，因此乘0.001；byte自动缩放到0.0-1.0之间，因此乘255
	if(vByte.a > 0.5)
	{
		return -(vByte.b + vByte.g * 256.0 + vByte.r * 65536.0) * 0.255;
	}
	else
	{
		return (vByte.b + vByte.g * 256.0 + vByte.r * 65536.0) * 0.255;
	}
	
}

//计算根据地形纹理坐标计算海拔高度
//eleTexCoord 顶点在精细层地形纹理上的纹理坐标
float CalculateElevation(vec2 eleTexCoord, sampler2D texture)
{
	float height = 0.0;
	//不是使用浮点纹理存储高程
	if(fFloatTexture > 0.1)
	{
		vec4 vec4height = texture2DLod(texture,eleTexCoord.xy, 0.0).xyzw;
		height = Convert4ByteToFloat(vec4height);
	}
	else
	{
		height = texture2DLod(texture,eleTexCoord.xy, 0.0).x;
	}
	return height * terrainScale;	
}

//计算顶点的世界坐标
//fElevation 海拔高度
vec3 CalculatePosition(float fElevation)
{	
	//用第二重纹理坐标存储了顶点坐标的低位
	vec3 positionLow = gl_Normal.xyz;
	vec3 positionHigh = gl_Vertex.xyz;

	vec2 xPOS = vec2(positionHigh.x, positionLow.x);
	vec2 yPOS = vec2(positionHigh.y, positionLow.y);
	vec2 zPOS = vec2(positionHigh.z, positionLow.z);

	vec2 xTerrainPOS = vec2(0.0);
	vec2 yTerrainPOS = vec2(0.0);
	vec2 zTerrainPOS = vec2(fElevation, 0.0);
	//判断是否为球面坐标系
	if(fPlanetRadius > 1.5)
	{
		vec2 Scale = vec2(fElevation, 0.0);
		xTerrainPOS = df64_mult(Scale, xPOS);
		yTerrainPOS = df64_mult(Scale, yPOS);
		zTerrainPOS = df64_mult(Scale, zPOS);
	}

	vec3 t1 = positionLow - vEyePosLow;
	vec3 e = t1 - positionLow;
	vec3 t2 = ((-vEyePosLow - e) + (positionLow - (t1 - e))) + positionHigh - vEyePosHigh;
	vec3 highDifference = t1 + t2;
	vec3 lowDifference = t2 - (highDifference - t1);

	vec2 xGlobalPOS = vec2(highDifference.x * fPlanetRadius, lowDifference.x * fPlanetRadius);
	vec2 yGlobalPOS = vec2(highDifference.y * fPlanetRadius, lowDifference.y * fPlanetRadius);
	vec2 zGlobalPOS = vec2(highDifference.z * fPlanetRadius, lowDifference.z * fPlanetRadius);

	xPOS = df64_Add(xTerrainPOS, xGlobalPOS);
	yPOS = df64_Add(yTerrainPOS, yGlobalPOS);
	zPOS = df64_Add(zTerrainPOS, zGlobalPOS);

	highDifference = vec3(xPOS.x, yPOS.x, zPOS.x);
	lowDifference = vec3(xPOS.y, yPOS.y, zPOS.y);

	return (highDifference + lowDifference);
}

vec2 CalculateTexCoord(vec2 eyeTexCoordLow, vec2 eyeTexCoordHigh)
{
	vec2 texCoordHigh = gl_MultiTexCoord0.xy;
	vec2 texCoordLow = gl_MultiTexCoord1.xy;

	vec2 t1 = texCoordLow - eyeTexCoordLow;
	vec2 e = t1 - texCoordLow;
	vec2 t2 = ((-eyeTexCoordLow - e) + (texCoordLow - (t1 - e))) + texCoordHigh - eyeTexCoordHigh;
	vec2 highDifference = t1 + t2;
	vec2 lowDifference = t2 - (highDifference - t1);

	return (highDifference + lowDifference);
}

//计算用来在地形纹理上采样的纹理坐标
//relTexCoord 相对视点的纹理坐标
//elevTexCoord 输出顶点的地形纹理坐标
//返回是否在边界
bool CalculateElevationTexCoordAndLevel(out vec2 elevTexCoord, out vec2 coarseElevTexCoord)
{
	//地形 各层的纹理坐标
	vec4 elevRelTexCoord = vec4(CalculateTexCoord(vec2(fEyeElevTexcoordLowX, fEyeElevTexcoordLowY), vec2(fEyeElevTexcoordHighX, fEyeElevTexcoordHighY)),0.0,1.0);

	bool bBoundary = true;

	if (isPointInRegionExt(elevRelTexCoord.xy, elevBound))
	{
		elevTexCoord = (elevTextureMatrix * elevRelTexCoord).xy;
		coarseElevTexCoord = (coarseElevTextureMatrix * elevRelTexCoord).xy;
		bBoundary = false;
	}
	else if (isPointInRegionExt(elevRelTexCoord.xy, coarseElevBound))
	{
		elevTexCoord = (coarseElevTextureMatrix * elevRelTexCoord).xy;
	}
	
	elevTexCoord = fract(elevTexCoord);
	elevTexCoord = clamp(elevTexCoord, 0.0 + fOffset, 1.0 - fOffset);

	coarseElevTexCoord = fract(coarseElevTexCoord);
	coarseElevTexCoord = clamp(coarseElevTexCoord, 0.0 + fOffset, 1.0 - fOffset);

	return bBoundary;
}

// The scale equation calculated by Vernier's Graphical Analysis.
float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

// Returns the near intersection point of a line and a sphere
float getNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}

// Returns the luminance of an RGB color.

float getLuminance(vec3 color)

{
	const vec3 luminance = vec3(0.3, 0.59, 0.11);

	return dot(luminance, color);

}

void CalAtmosphereScatterParameters(vec4 vWorldPos)
{
	// Get the ray from the camera to the vertex and its length
	// (which is the far point of the ray passing through the atmosphere)
	vec3 v3Pos = vec3(modelMatrix * vWorldPos / fPlanetRadius);
	 vertNorm = normalize(gl_Vertex.xyz);
	vec3 v3Ray = v3Pos - v3CameraPos;
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	vLight = v3LightPos;
	float nDotL = dot(vertNorm, v3LightPos);

	nDotL = clamp(fKSunColor * nDotL, 0.0, 1.0);
	
	// Calculate the ray's starting position
	vec3 v3Start = v3CameraPos;
	if (fCameraHeight >= fOuterRadius)

	{

		float fNear = getNearIntersection(v3CameraPos, v3Ray, fCameraHeight2, fOuterRadius2);

		v3Start += v3Ray * fNear;
		fFar -= fNear;
	}

	// Initial scattering offset.
	float fStartDepth = v3StartupConsts.x;
	// Calculate its scattering offset
	float fCameraAngle = max(0.0, dot(-v3Ray, vertNorm));
	float fLightAngle = dot(v3LightPos, vertNorm);
	float fCameraScale = scale(fCameraAngle);
	float fLightScale = scale(fLightAngle);
	float fCameraOffset = fStartDepth*fCameraScale;
	float fScaleSum = (fLightScale + fCameraScale);

	// Initialize the scattering loop variables
	float fSampleLength = fFar / float(nSamples);
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

	// Now loop through the sample rays
	vec3 v3FrontColor = vec3(0.0);
	vec3 v3Attenuate;
	for(int i=0; i<nSamples; i++)
	{
		float fSampleHeight = length(v3SamplePoint);
		float fSampleDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fSampleHeight));
		float fSampleScatter = fSampleDepth*fScaleSum - fCameraOffset;
		v3Attenuate = exp(-fSampleScatter * (v3InvWavelength * fKr4PI + fKm4PI));
		v3FrontColor += v3Attenuate * (fSampleDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}
	
	float horizonExp = v3StartupConsts.y;
	float rayleighToneDownScale = v3StartupConsts.z;
	float closeToHorizon = 1.0 - fCameraAngle;

	float closeToCamera = 1.0 - closeToHorizon*closeToHorizon;
	// Compute rayleigh scale factor. Higher closer to horizon and at higher altitudes.
	float scaledRayleighFactor = rayleighToneDownScale * pow(closeToHorizon, horizonExp);
	
	vec3 kBaseAmbientColor = vec3(0.12, 0.12, 0.15);
	float darkShadedAmbientFactor = 1.0 - nDotL;
	float nightAmbientTemp = getLuminance(v3Attenuate);
	float nightAmbientFactor = 1.0 - nightAmbientTemp * nightAmbientTemp;
	float ambientFactor = closeToCamera * (darkShadedAmbientFactor + nightAmbientFactor);
	vec3 headlampAmbientContribution = kBaseAmbientColor * ambientFactor;
	vec3 sunsetAmbient = v4SunsetAmbientAndFogDensity.xyz;
	vec3 ambientContribution = headlampAmbientContribution + sunsetAmbient;

	float closeToNoon = dot(v3CameraPos, v3LightPos) / length(v3CameraPos);
	float closeToNoonFactor = closeToCamera * closeToNoon;

	float fogDensity = v4SunsetAmbientAndFogDensity.w;
	float fogTemp = fogDensity * fFar;
	fFogFactor = exp(-(fogTemp * fogTemp));

	const vec3 kMaxRayleighContribution = vec3(0.5, 0.5, 0.8);
	vec3Rayleigh = min(kMaxRayleighContribution,
		v3FrontColor * (v3InvWavelength * fKrESun + fKmESun) * scaledRayleighFactor);
	// Compute Mie color.
	vec3 mieColor = v3Attenuate;
	vec3 adjustedMieColor = clamp(
		(mieColor + vec3(closeToNoonFactor)) * nDotL + ambientContribution, 0.0, 1.0);
	vec3AdjustedMie = adjustedMieColor;
}

void main()
{
	mixColor = ambient_light_colour*surface_ambient_colour
		+ light_diffuse_colour*surface_diffuse_colour
		+ light_specular_colour*surface_specular_colour;
	mixColor = clamp(mixColor, vec4(0.0), vec4(1.0));
	
	globalBound = globalBoundary;
	//影像 各层的纹理坐标
	vec4 imgTexCoord = vec4(CalculateTexCoord(vec2(fEyeTexcoordLowX, fEyeTexcoordLowY), vec2(fEyeTexcoordHighX, fEyeTexcoordHighY)),0.0,1.0);
	gl_TexCoord[0].xy = (texture0Matrix * imgTexCoord).xy;
	gl_TexCoord[1].xy = (texture1Matrix * imgTexCoord).xy;
	gl_TexCoord[2].xy = (texture2Matrix * imgTexCoord).xy;
	gl_TexCoord[3].xy = (texture3Matrix * imgTexCoord).xy;

	texCoord.xy = imgTexCoord.xy;

	//顶点世界坐标
	vec4 pos;
	//顶点法线
	realNormal = vec3(0.0, 0.0, 1.0);

	//判断顶点是否在有地形的区域范围内
	if (hasTerrainData > 0)
	{
		//保存顶点在精细层地形纹理上的纹理坐标
		vec2 elevationTexCoord = vec2(0.0);

		vec2 coarseElevationTexCoord = vec2(0.0);
		//计算顶点在地形纹理中的纹理坐标
		bool bBoundary = CalculateElevationTexCoordAndLevel(elevationTexCoord, coarseElevationTexCoord);

		//计算顶点在地形纹理中的高程
		float fElevation = 0.0;

		//计算顶点在粗糙层地形纹理中的高程
		float fCoarseElevation;

		float fMorph = 1.0;

		if(bBoundary)
		{
			if(nTerrainLevel > 0)
			{
				fElevation = CalculateElevation(elevationTexCoord, coarseElevationTexture);
			}
			pos = vec4(CalculatePosition(fElevation), 1.0);
		}
		else
		{
			fElevation = CalculateElevation(elevationTexCoord, elevationTexture);

			if(nTerrainLevel == 0)
			{
				fCoarseElevation = 0.0;
			}
			else
			{
				fCoarseElevation = CalculateElevation(coarseElevationTexCoord, coarseElevationTexture);
			}


			if (nTerrainLevel > 3)
			{
				//计算融合系数
				float fDistance = length(CalculatePosition(0.0));

				float fMorphDistance = 32.0 * fDistance / fMaxDistance; //粗糙层的比重
				fMorph = fMorphSpace * ( 1.0 - clamp(fMorphDistance, 0.0, 1.0) );
			}

			//计算顶点坐标
			pos = vec4(CalculatePosition(fElevation * fMorph + fCoarseElevation * (1.0 - fMorph)), 1.0);
		}

		if (fTopLev > 0.0)
		{
			if(bBoundary)
			{
				realNormal = normalize(texture2DLod(coarseElevationNormalTexture, elevationTexCoord, 0.0).xyz);
			}
			else
			{	
				vec3 realFineNormal = normalize(texture2DLod(elevationNormalTexture, elevationTexCoord, 0.0).xyz);
				vec3 realCoarseNormal = normalize(texture2DLod(coarseElevationNormalTexture, coarseElevationTexCoord, 0.0).xyz);

				vec3 vMorph = vec3(fMorph);
				realNormal = mix(realCoarseNormal, realFineNormal, vMorph);
			}
		}

	}
	else
	{
		//计算顶点坐标
		pos = vec4(CalculatePosition(0.0), 1.0);
	}

	// 顶点坐标变换
	gl_Position = gl_ModelViewProjectionMatrix * pos;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

#if CLIP
	// 裁剪坐标
	clip_vertex = worldview_matrix * pos;
#endif

	//计算大气散射参数
	CalAtmosphereScatterParameters(pos);
}
