uniform float Time;

//���λ��
uniform vec3 EyePos;
uniform float fVisibleDist;

//�ӵ�λ��
uniform vec3 LookAtPos;

uniform float fEyeTexcoordHighX;
uniform float fEyeTexcoordHighY;
uniform float fEyeTexcoordLowX;
uniform float fEyeTexcoordLowY;

//�����б��
uniform float CamTilt;

//���λ�ã��������������ֵ�λ�͸�λ
uniform vec3 vEyePosHigh;
uniform vec3 vEyePosLow;
uniform float scale;
uniform vec4 TexcoordTranslate;

varying vec3  ViewVec;
varying vec4 v_color;
varying vec2 bumpCoord0;
varying vec3 LightDir;
varying float specPow;
//�����������
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

//��ö�������������ϵ�µ�����
void CalculateWorldPosition(out vec3 positionHigh, out vec3 positionLow)
{
	//ԭʼ�ĵ�����
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

//���㶥��������ӵ������
vec3 CalPosRelateToEye()
{
	//ԭʼ�ĵ�����
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
	// ��һ���߶ȵ��ӵ㣬���ڵ�����
	float fEyeHeight = length(EyePos);

	vec3 pos = (GLOBAL_RADIUS * normalize(EyePos) + LookAtPos) / 2.0;
	float len = length(EyePos - pos);

	//ԭʼ�ĵ�����
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
	// �����ص���ʾ�������
	float dOceanClear = 1.0 - (fEyeHeight  - GLOBAL_RADIUS - fVisibleDist * 0.8) / 100000.0;
	dOceanClear = clamp(dOceanClear, 0.0, 1.0);
	v_color.w *= dOceanClear;

	// �������汾������ϵ������ת��������������������
	vec3 Tangent = vec3(-vOriginal.y, vOriginal.x, 0);	// ԭʼ�㴦�ķ�����
	vec3 n = normalize(vOriginal);
	vec3 t = normalize(Tangent);
	vec3 b = cross(n, t);
	
	// ��������������������ת�þ�������ʣ��������ת��
	// ����ļ�������������Ծ������ʽ����ͬ�ھ����ת�ó�������
	mat3 transform= mat3(t, b, n);
	LightDir = normalize(LightPos * transform);
	ViewVec = normalize((-EyePos) * transform);

	vec4 texCoordEx = vec4(CalculateTexCoordScale(), 0.0, 1.0);
	texCoordEx += TexcoordTranslate;
	vec4 texCoord = vec4(CalculateTexCoord(), 0.0, 1.0);
	texCoord += TexcoordTranslate;
	
	// ��ͼ
	gl_TexCoord[0] = gl_TextureMatrix[0] * texCoordEx;
	gl_TexCoord[2] = gl_TextureMatrix[2] * texCoord;
	
	//�ֲ��ģ�����������
	vec4 texCoordLocal = vec4(gl_MultiTexCoord0.x, gl_MultiTexCoord0.y, 0.0, 1.0);
	gl_TexCoord[3] = gl_TextureMatrix[3] * texCoordLocal;	
	gl_TexCoord[4] = gl_TextureMatrix[4] * texCoordLocal;
	gl_TexCoord[5] = gl_TextureMatrix[5] * texCoordLocal;
	
	// calculate texture coordinates for normal map lookup
	vec4 vOff;
	vOff.xy = vec2(0.707, -0.707) * Time  * 0.0001;
	
	// ����
	bumpCoord0.xy = (gl_TexCoord[0] - vOff).xy;

	gl_Position = gl_ModelViewProjectionMatrix * vec4(CalPosRelateToEye(), 1.0);
}
