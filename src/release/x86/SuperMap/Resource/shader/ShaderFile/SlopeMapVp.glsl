
uniform mat4 texture0Matrix;
uniform mat4 texture1Matrix;
uniform mat4 texture2Matrix;
uniform mat4 texture3Matrix;

uniform mat4 elevTextureMatrix;
uniform mat4 coarseElevTextureMatrix;

// ��������߽�
uniform vec4 elevBound;
uniform vec4 coarseElevBound;

uniform int nTerrainLevel;


//�ں�
uniform float fMorphSpace;
uniform float fMaxDistance;

uniform vec4 globalBoundary;	// ȫ������߽�
uniform float fTopLev; //��ֲڲ���

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


uniform float terrainScale;
uniform float fFloatTexture;
uniform int hasTerrainData;

varying vec3 realNormal;
varying vec2 texCoordRotate;
varying vec2 texCoord;
const float fOffset = 0.001953125;

// �жϵ��Ƿ��ھ�����
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x&& point.x<region.z
		&& point.y<region.y&& point.y>region.w);
}

bool isPointInRegionExt(vec2 point, vec4 region)
{
	if (region.x > region.z)
	{
		// ��Խȫ��߽�����
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

//��������RGBAͨ���е��ĸ�byte��ԭΪfloat
float Convert4ByteToFloat(vec4 vByte)
{
	//b,g,r,aͨ���ֱ𱣴���ԭʼ�߶ȵ��ĸ�byte�������Ҫ�������λ�ƻ�ԭ��ԭ����λ��aͨ���洢�߶�ֵ�Ƿ�Ϊ��ֵ��1Ϊ��ֵ��0Ϊ��ֵ
	//�߶���CPU��������һǧ������˳�0.001��byte�Զ����ŵ�0.0-1.0֮�䣬��˳�255
	if(vByte.a > 0.5)
	{
		return -(vByte.b + vByte.g * 256.0 + vByte.r * 65536.0) * 0.255;
	}
	else
	{
		return (vByte.b + vByte.g * 256.0 + vByte.r * 65536.0) * 0.255;
	}
	
}

//������ݵ�������������㺣�θ߶�
//eleTexCoord �����ھ�ϸ����������ϵ���������
float CalculateElevation(vec2 eleTexCoord, sampler2D texture)
{
	float height = 0.0;
	//����ʹ�ø�������洢�߳�
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

//���㶥�����������
//fElevation ���θ߶�
vec3 CalculatePosition(float fElevation)
{	
	//�õڶ�����������洢�˶�������ĵ�λ
	vec3 positionLow = gl_Normal.xyz;
	vec3 positionHigh = gl_Vertex.xyz;

	vec2 xPOS = vec2(positionHigh.x, positionLow.x);
	vec2 yPOS = vec2(positionHigh.y, positionLow.y);
	vec2 zPOS = vec2(positionHigh.z, positionLow.z);

	vec2 xTerrainPOS = vec2(0.0);
	vec2 yTerrainPOS = vec2(0.0);
	vec2 zTerrainPOS = vec2(fElevation, 0.0);
	//�ж��Ƿ�Ϊ��������ϵ
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

//����������������������꣬����ֲڵ���һ����������
bool CalculateSlopeElevationTexCoord(out vec2 elevTexCoord, out vec2 coarserElevTexCoord)
{
	texCoord = CalculateTexCoord(vec2(fEyeElevTexcoordLowX, fEyeElevTexcoordLowY), vec2(fEyeElevTexcoordHighX, fEyeElevTexcoordHighY));
	vec4 elevRelTexCoord = vec4(texCoord,0.0,1.0);

	elevTexCoord = vec2(0.0);
	coarserElevTexCoord = vec2(0.0);
	bool bNeedMorph = false;
	
	if (fTopLev<=8)
	{
		elevTexCoord = (coarseElevTextureMatrix * elevRelTexCoord).xy;
	}
	else if(fTopLev <= 9)
	{
		if (isPointInRegionExt(texCoord, elevBound))
		{
			elevTexCoord = (elevTextureMatrix * elevRelTexCoord).xy;
		}
		else
		{
			elevTexCoord = (coarseElevTextureMatrix * elevRelTexCoord).xy;
		}
	}

	//���ݲ��ģ4��ֵȷ���ڵ��δ������ϵ�λ��
	elevTexCoord = fract(elevTexCoord);
	elevTexCoord = clamp(elevTexCoord, 0.0 + fOffset, 1.0 - fOffset);

	return bNeedMorph;
}

//���������ڵ��������ϲ�������������
//relTexCoord ����ӵ����������
//elevTexCoord �������ĵ�����������
//�����Ƿ��ڱ߽�
bool CalculateElevationTexCoordAndLevel(out vec2 elevTexCoord, out vec2 coarseElevTexCoord)
{
	//���� �������������
	vec4 elevRelTexCoord = vec4(CalculateTexCoord(vec2(fEyeElevTexcoordLowX, fEyeElevTexcoordLowY), vec2(fEyeElevTexcoordHighX, fEyeElevTexcoordHighY)),0.0,1.0);

	bool bBoundary = false; 

	if (isPointInRegionExt(elevRelTexCoord.xy, elevBound))
	{
		elevTexCoord = (elevTextureMatrix * elevRelTexCoord).xy;
		coarseElevTexCoord = (coarseElevTextureMatrix * elevRelTexCoord).xy;
	}
	else if (isPointInRegionExt(elevRelTexCoord.xy, coarseElevBound))
	{
		elevTexCoord = (coarseElevTextureMatrix * elevRelTexCoord).xy;
		bBoundary = true;
	}
	
	elevTexCoord = fract(elevTexCoord);
	elevTexCoord = clamp(elevTexCoord, 0.0 + fOffset, 1.0 - fOffset);

	coarseElevTexCoord = fract(coarseElevTexCoord);
	coarseElevTexCoord = clamp(coarseElevTexCoord, 0.0 + fOffset, 1.0 - fOffset);

	return bBoundary;
}

void main()
{
	//������������
	vec4 pos;
	//���㷨��
	realNormal = vec3(0.0, 0.0, 1.0);

	//�ж϶����Ƿ����е��ε�����Χ��
	if (hasTerrainData > 0)
	{
		//���涥���ھ�ϸ����������ϵ���������
		vec2 elevationTexCoord = vec2(0.0);

		vec2 coarseElevationTexCoord = vec2(0.0);
		//���㶥���ڵ��������е���������
		bool bBoundary = CalculateElevationTexCoordAndLevel(elevationTexCoord, coarseElevationTexCoord);

		//���㶥���ڵ��������еĸ߳�
		float fElevation;

		//���㶥���ڴֲڲ���������еĸ߳�
		float fCoarseElevation;

		float fMorph = 1.0;

		if(bBoundary)
		{
			fElevation = CalculateElevation(elevationTexCoord, coarseElevationTexture);
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

			if (nTerrainLevel > 3.5)
			{
				//�����ں�ϵ��
				float fDistance = length(CalculatePosition(0.0));

				float fMorphDistance = 32.0 * fDistance / fMaxDistance; //�ֲڲ�ı���
				fMorph = fMorphSpace * ( 1.0 - clamp(fMorphDistance, 0.0, 1.0) );
			}

			//���㶥������
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
		//���㶥������
		pos = vec4(CalculatePosition(0.0), 1.0);
	}

	texCoord = CalculateTexCoord(vec2(fEyeElevTexcoordLowX, fEyeElevTexcoordLowY), vec2(fEyeElevTexcoordHighX, fEyeElevTexcoordHighY));

	//�����������������
	texCoordRotate.x = texCoord.x * pow(2.0,fTopLev + 3.0) * 128.0 + 0.125;
	texCoordRotate.y = texCoord.y * pow(2.0,fTopLev + 3.0) * 64.0 + 0.125;

	// ��������任
	gl_Position = gl_ModelViewProjectionMatrix * pos;
}