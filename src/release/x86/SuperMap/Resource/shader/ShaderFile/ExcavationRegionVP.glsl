uniform mat4 texture0Matrix;
uniform mat4 texture1Matrix;
uniform mat4 texture2Matrix;
uniform mat4 texture3Matrix;
uniform mat4 texture4Matrix;

//�ں�
uniform float fMorphSpace;
uniform float fMaxDistance;

// ��������߽�
uniform vec4 elev0Bound;
uniform vec4 elev1Bound;
uniform vec4 elev2Bound;
uniform vec4 elev3Bound;
uniform vec4 elev4Bound;

uniform vec4 globalBoundary;	// ȫ������߽�
uniform vec4 terrainDataBound;  // �������ݷ�Χ�߽�
uniform float fTopLev; //��ֲڲ���

uniform sampler2D elevationTexture0;
uniform sampler2D elevationTexture1;
uniform sampler2D elevationTexture2;
uniform sampler2D elevationTexture3;
uniform sampler2D elevationTexture4;

uniform vec3 vEyePosHigh;
uniform vec3 vEyePosLow;

uniform float fPlanetRadius;

uniform float fEyeTexcoordHighX;
uniform float fEyeTexcoordHighY;
uniform float fEyeTexcoordLowX;
uniform float fEyeTexcoordLowY;
uniform float terrainScale;
uniform float fFloatTexture;
uniform int hasTerrainData;

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


vec2 CalculateTexCoord()
{
	vec2 texCoordHigh = gl_MultiTexCoord1.xy;
	vec2 texCoordLow = gl_MultiTexCoord1.zw;
	vec2 eyeTexCoordLow = vec2(fEyeTexcoordLowX, fEyeTexcoordLowY);
	vec2 eyeTexCoordHigh = vec2(fEyeTexcoordHighX, fEyeTexcoordHighY);

	vec2 t1 = texCoordLow - eyeTexCoordLow;
	vec2 e = t1 - texCoordLow;
	vec2 t2 = ((-eyeTexCoordLow - e) + (texCoordLow - (t1 - e))) + texCoordHigh - eyeTexCoordHigh;
	vec2 highDifference = t1 + t2;
	vec2 lowDifference = t2 - (highDifference - t1);

	return (highDifference + lowDifference);
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
float CalculateElevation(vec2 eleTexCoord, sampler2D elevationTexture)
{

	float height = 0.0;
	//����ʹ�ø�������洢�߳�
	if(fFloatTexture > 0.1)
	{
		vec4 vec4height = texture2DLod(elevationTexture,eleTexCoord.xy, 0.0).xyzw;
		height = Convert4ByteToFloat(vec4height);
	}
	else
	{
		height = texture2DLod(elevationTexture,eleTexCoord.xy, 0.0).x;
	}

	height += gl_MultiTexCoord2.x;
	return height * terrainScale;	
}

//���������ڵ��������ϲ�������������
//relTexCoord ����ӵ����������
//fElevation ���θ߶�
//fCoarseElevation �ֲڵ��θ߶�
//�����Ƿ��ںϣ����ֲ������Ƿ�����
bool CalculateMorphElevation(vec2 relTexCoord, out float fElevation, out float fCoarseElevation)
{
	vec2 elevTexCoord = vec2(0.0);
	vec2 coarseElevTexCoord = vec2(0.0);

	float fLevel;

	bool bMorph = false;
	
	//����ж϶������䵽���ϸtile�����Ĳ�
	if (isPointInRegionExt(relTexCoord, elev4Bound))
	{
		elevTexCoord = (texture4Matrix * vec4(relTexCoord, 0.0, 1.0)).xy;

		fLevel = 4;

		coarseElevTexCoord = (texture3Matrix * vec4(relTexCoord, 0.0, 1.0)).xy;

		coarseElevTexCoord = fract(coarseElevTexCoord);
		coarseElevTexCoord = clamp(coarseElevTexCoord, 0.0 + fOffset, 1.0 - fOffset);

		bMorph = true;
	}
	else if (isPointInRegionExt(relTexCoord, elev3Bound))
	{
		elevTexCoord = (texture3Matrix * vec4(relTexCoord, 0.0, 1.0)).xy;

		fLevel = 3;
	}
	else if (isPointInRegionExt(relTexCoord, elev2Bound))
	{
		elevTexCoord = (texture2Matrix * vec4(relTexCoord, 0.0, 1.0)).xy;

		fLevel = 2;
	}
	else if (isPointInRegionExt(relTexCoord, elev1Bound))
	{
		elevTexCoord = (texture1Matrix * vec4(relTexCoord, 0.0, 1.0)).xy;

		fLevel = 1;
	}
	else
	{
		elevTexCoord= (texture0Matrix * vec4(relTexCoord, 0.0, 1.0)).xy;

		fLevel = 0;
	}


	elevTexCoord = fract(elevTexCoord);
	elevTexCoord = clamp(elevTexCoord, 0.0 + fOffset, 1.0 - fOffset);


	float modLev = mod(fTopLev + fLevel, 5.0);
	if(modLev > 3.5)
	{
		fElevation = CalculateElevation(elevTexCoord, elevationTexture4);

		if(bMorph)
		{
			fCoarseElevation = CalculateElevation(coarseElevTexCoord, elevationTexture3);
		}
	}
	else if(modLev > 2.5)
	{
		fElevation = CalculateElevation(elevTexCoord, elevationTexture3);

		if(bMorph)
		{
			fCoarseElevation = CalculateElevation(coarseElevTexCoord, elevationTexture2);
		}
	}
	else if(modLev > 1.5)
	{
		fElevation = CalculateElevation(elevTexCoord, elevationTexture2);

		if(bMorph)
		{
			fCoarseElevation = CalculateElevation(coarseElevTexCoord, elevationTexture1);
		}
	}
	else if(modLev > 0.5)
	{
		fElevation = CalculateElevation(elevTexCoord, elevationTexture1);

		if(bMorph)
		{
			fCoarseElevation = CalculateElevation(coarseElevTexCoord, elevationTexture0);
		}
	}
	else
	{
		fElevation = CalculateElevation(elevTexCoord, elevationTexture0);

		if(bMorph)
		{
			fCoarseElevation = CalculateElevation(coarseElevTexCoord, elevationTexture4);
		}
	}

	return bMorph;
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

void main()
{
	//������������
	vec4 pos;
	
	//�ж϶����Ƿ����е��ε�����Χ��
	if (hasTerrainData > 0)
	{
		//���涥���ھ�ϸ�㼰�ֲڲ���������ϵ���������
		vec2 elevationTexCoord = vec2(0.0);
		vec2 coarseElevationTexCoord = vec2(0.0);

		//��������
		vec2 texCoord = CalculateTexCoord();

		//���㶥���ڴֲڲ���������еĸ߳�
		float fCoarseElevation = 0.0;

		//���㶥���ڵ��������еĸ߳�
		float fElevation = 0.0;

		bool bMorph = CalculateMorphElevation(texCoord, fElevation, fCoarseElevation);
		
		//�����ں�ϵ��
		float fMorph = 1.0;

		if (bMorph)
		{
			float fDistance = length(CalculatePosition(0.0));
			float fMorphDistance = 32 * fDistance / fMaxDistance; //�ֲڲ�ı���
			fMorph = fMorphSpace * ( 1.0 - clamp(fMorphDistance, 0.0, 1.0) );
		}

		//���㶥������
		pos = vec4(CalculatePosition(fElevation * fMorph + fCoarseElevation * (1.0 - fMorph)), 1.0);
		
	}
	else
	{
		//���㶥������
		pos = vec4(CalculatePosition(0.0), 1.0);
	}

	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	// ��������任
	gl_Position = gl_ModelViewProjectionMatrix * pos;
}
