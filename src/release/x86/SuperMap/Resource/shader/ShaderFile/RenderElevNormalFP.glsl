uniform sampler2D elevationTexture;
// ��������߽�
uniform vec4 elevBounds;
// �Ƿ���ƽ�泡�� 0:ƽ�泡����1�����泡��
uniform int isEarth;

const float step = 0.001953125;

const float fPlanetRadius = 6378137.0;	// ����뾶

//���㵱ǰ�����ݶȲ�����֮���ʵ�ʾ���
vec2 ComputeRealStep()
{
	vec2 realStep = vec2(0.0);
	//���ȷ����ϵ�ǰ��Ŀ��
	float dLongSpan = elevBounds.z - elevBounds.x;
	//γ�ȷ����ϵ�ǰ��Ŀ��
	float dLatSpan = elevBounds.y - elevBounds.w;
	
	realStep.x = dLongSpan * step;
	realStep.y = dLatSpan * step;
	if (isEarth == 1)
	{
		//���������������γ��
		float dLat = elevBounds.w + dLatSpan * (1.0 - gl_TexCoord[0].y);
		//��ǰγ���϶�Ӧ��СԲ�뾶
		float fRadius = fPlanetRadius * cos(dLat);
		//����һ������step��Ӧ�ĳ���
		realStep.x = fRadius * dLongSpan * step;
		realStep.y = fPlanetRadius * dLatSpan * step;
	}
	
	return realStep;
}

vec3 ComputeNormalCentralDifference()
{
	vec2 TexCoord = clamp(gl_TexCoord[0].xy, 0.0 + step * 1.125, 1.0 - step * 1.125);
	float west = texture2D(elevationTexture,(TexCoord + vec2(-1.0, 0.0) * step)).r;
	float east = texture2D(elevationTexture,(TexCoord + vec2(1.0, 0.0) * step)).r;
	float north = texture2D(elevationTexture,(TexCoord + vec2(0.0, 1.0) * step)).r;
	float south = texture2D(elevationTexture,(TexCoord + vec2(0.0, -1.0) * step)).r;

	vec2 realStep = ComputeRealStep();
	return normalize(vec3((west - east) / realStep.x, (south - north) / realStep.y, 2.0));
}

void main()
{	
	gl_FragColor = vec4(ComputeNormalCentralDifference(), 1.0);
}