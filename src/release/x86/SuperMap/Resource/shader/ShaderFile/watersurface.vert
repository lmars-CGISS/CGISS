uniform float Time;

//相机位置
uniform vec3 EyePos;
uniform float fVisibleDist;

//视点位置
uniform vec3 LookAtPos;

uniform float fEyeTexcoordHighX;
uniform float fEyeTexcoordHighY;
uniform float fEyeTexcoordLowX;
uniform float fEyeTexcoordLowY;

//相机倾斜角
uniform float CamTilt;

//相机位置，用来反抖动，分低位和高位
uniform vec3 vEyePosHigh;
uniform vec3 vEyePosLow;
uniform float scale;
uniform vec4 TexcoordTranslate;

varying vec3  ViewVec;
varying vec4 v_color;
varying vec2 bumpCoord0;
varying vec3 LightDir;
varying float specPow;
//反光调节因子
varying float factor;

const float PI = 3.14159;
const float GLOBAL_RADIUS = 6378137.0;
//const vec3 LightPos = vec3(0, 0, 100000);

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
	float t = a * 4097;
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

//获得顶点在世界坐标系下的坐标
void CalculateWorldPosition(out vec3 positionHigh, out vec3 positionLow)
{
	//原始的点数据
	positionLow = gl_Normal.xyz;
	positionHigh = gl_Vertex.xyz;

	vec2 Scale = vec2(GLOBAL_RADIUS, 0.0);

	vec2 xPOS = vec2(positionHigh.x, positionLow.x);
	vec2 yPOS = vec2(positionHigh.y, positionLow.y);
	vec2 zPOS = vec2(positionHigh.z, positionLow.z);

	xPOS = df64_mult(Scale, xPOS);
	yPOS = df64_mult(Scale, yPOS);
	zPOS = df64_mult(Scale, zPOS);

	positionHigh = vec3(xPOS.x, yPOS.x, zPOS.x);
	positionLow = vec3(xPOS.y, yPOS.y, zPOS.y);
}

//计算顶点相对于视点的坐标
vec3 CalPosRelateToEye()
{
	//原始的点数据
	vec3 positionLow = gl_Normal.xyz;
	vec3 positionHigh = gl_Vertex.xyz;

	vec3 t1 = positionLow - vEyePosLow;
	vec3 e = t1 - positionLow;
	vec3 t2 = ((-vEyePosLow - e) + (positionLow - (t1 - e))) + positionHigh - vEyePosHigh;
	vec3 highDifference = t1 + t2;
	vec3 lowDifference = t2 - (highDifference - t1);

	return (highDifference + lowDifference) * GLOBAL_RADIUS;
}

vec2 CalculateTexCoordScale()
{
	vec2 texCoordHigh = fract(gl_MultiTexCoord0.xy * scale);
	vec2 texCoordLow = fract(gl_MultiTexCoord0.zw * scale);
	vec2 eyeTexCoordLow = fract(vec2(fEyeTexcoordLowX, fEyeTexcoordLowY)*scale);
	vec2 eyeTexCoordHigh = fract(vec2(fEyeTexcoordHighX, fEyeTexcoordHighY)*scale);

	vec2 t1 = texCoordLow - eyeTexCoordLow;
	vec2 e = t1 - texCoordLow;
	vec2 t2 = ((-eyeTexCoordLow - e) + (texCoordLow - (t1 - e))) + texCoordHigh - eyeTexCoordHigh;
	vec2 highDifference = t1 + t2;
	vec2 lowDifference = t2 - (highDifference - t1);

	return (highDifference + lowDifference);
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

void main(void)
{
	// 有一定高度的视点，不在地面上
	float fEyeHeight = length(EyePos);

	vec3 pos = (GLOBAL_RADIUS * normalize(EyePos) + LookAtPos) / 2.0;
	float len = length(EyePos - pos);

	//原始的点数据
	vec3 positionLow = vec3(0.0);
	vec3 positionHigh = vec3(0.0);
	CalculateWorldPosition(positionHigh, positionLow);

	vec3 vOriginal = positionHigh + positionLow;
	float dis = length(vOriginal - EyePos );
	
	factor = dis / ((fEyeHeight - GLOBAL_RADIUS) * sin(CamTilt * 0.6) + ( 1.0 - sin(CamTilt * 0.6)) * len);
	
	specPow = (fEyeHeight  - GLOBAL_RADIUS) / 10000.0;
	specPow = clamp(specPow, 16.0, 60.0);
	
	if(factor > 1.0)
	{
		specPow *= factor;
	}

	vec3 LightPos = vOriginal;

	v_color = vec4( 1.0, 1.0, 1.0, 0.7);	
	// 渐渐地地显示海洋表面
	float dOceanClear = 1.0 - (fEyeHeight  - GLOBAL_RADIUS - fVisibleDist * 0.8) / 100000.0;
	dOceanClear = clamp(dOceanClear, 0.0, 1.0);
	v_color.w *= dOceanClear;

	// 建立表面本地坐标系，用于转换光线向量和视线向量
	vec3 Tangent = vec3(-vOriginal.y, vOriginal.x, 0);	// 原始点处的法向量
	vec3 n = normalize(vOriginal);
	vec3 t = normalize(Tangent);
	vec3 b = cross(n, t);
	
	// 根据正交矩阵的逆等于其转置矩阵的性质，完成坐标转换
	// 下面的计算采用向量乘以矩阵的形式，等同于矩阵的转置乘以向量
	mat3 transform= mat3(t, b, n);
	LightDir = normalize(LightPos * transform);
	ViewVec = normalize((-EyePos) * transform);

	vec4 texCoordEx = vec4(CalculateTexCoordScale(), 0.0, 1.0);
	texCoordEx += TexcoordTranslate;
	vec4 texCoord = vec4(CalculateTexCoord(), 0.0, 1.0);
	texCoord += TexcoordTranslate;
	
	// 底图
	gl_TexCoord[0] = gl_TextureMatrix[0] * texCoordEx;
	gl_TexCoord[2] = gl_TextureMatrix[2] * texCoord;
	
	//局部的，不做反抖动
	vec4 texCoordLocal = vec4(gl_MultiTexCoord0.x, gl_MultiTexCoord0.y, 0.0, 1.0);
	gl_TexCoord[3] = gl_TextureMatrix[3] * texCoordLocal;	
	gl_TexCoord[4] = gl_TextureMatrix[4] * texCoordLocal;
	gl_TexCoord[5] = gl_TextureMatrix[5] * texCoordLocal;
	
	// calculate texture coordinates for normal map lookup
	vec4 vOff;
	vOff.xy = vec2(0.707, -0.707) * Time  * 0.0001;
	
	// 亮光
	bumpCoord0.xy = (gl_TexCoord[0] - vOff).xy;

	gl_Position = gl_ModelViewProjectionMatrix * vec4(CalPosRelateToEye(), 1.0);
}
