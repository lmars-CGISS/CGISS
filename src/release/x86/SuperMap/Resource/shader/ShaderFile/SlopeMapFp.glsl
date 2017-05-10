uniform sampler2D slopeColorTexture;
uniform sampler2D slopeArrowsTexture;
uniform vec4 selectAreaBound;//��ѡ���εı߽�
uniform int slopeFillMode;//�¶ȡ��������ʾģʽ
uniform float slopeOpacity;//͸����
uniform float floorAngle;
uniform float ceilAngle;
uniform float maxVisibleSlope;
uniform float minVisibleSlope;
uniform sampler2D slopePolygonTexture;

varying vec2 texCoord;
varying vec3 realNormal;
varying vec2 texCoordRotate;
const float PI = 3.1415926535897932384626;
// �жϵ��Ƿ��ھ�����
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}
void main()
{
	// ����㲻�ڶ���ε����Bound��ʱ������������
	if (!isPointInRegion(texCoord, selectAreaBound))
	{
		discard;
		return;
	}
	// ��������¶�ֵ
	float slopeRate = abs(normalize(realNormal).z);

	float slopeAngle = acos(slopeRate);
	//���¶Ȳ��ڷ�����Χʱ������
	if (slopeAngle < minVisibleSlope || slopeAngle > maxVisibleSlope)
	{
		discard;
		return;
	}
	// �Ѷ���ε�Bound�����µ����������任Ϊ(0.0,0.0)
	vec2 polygonTexCoord = texCoord - vec2(selectAreaBound.x, selectAreaBound.w);
	// С�������x,y��������ű���
	float xScale = 1.0 / (selectAreaBound.z - selectAreaBound.x);
	float yScale = 1.0 / (selectAreaBound.y - selectAreaBound.w);
	// ��С��������������ֵ�任��0~1֮�䡣
	polygonTexCoord.x = polygonTexCoord.x * xScale;
	polygonTexCoord.y = polygonTexCoord.y * yScale;
	//�¶���ֵ
	float threshold = clamp(abs(ceilAngle-floorAngle),0.0000001,PI/2.0);
	float rate = (slopeAngle-floorAngle)/threshold;
	float finalRate = clamp(rate,0.0,1.0);
	vec2 slopeCoord = vec2(0, finalRate);
	vec4 slope = texture2D(slopeColorTexture, slopeCoord);	
	vec4 finalColor = vec4(0.0);
	vec4 slopeFillColor = vec4(slope.xyz, slopeOpacity);
	//����	  �����������޶���(0.0,1.0)��
	vec2 limitTexCoord = fract(texCoordRotate);
	//���εķ�����XYƽ���ϵ�ͶӰ
	vec2 slopeDirection = realNormal.xy;
	vec4 arrowsTexColor = vec4(0.0);
	float arrowAlpha = 0.0;
	//��slopeDirectionΪ0ʱ����ʾһ��û�������ƽ��,����������
	if (slopeAngle>PI/180.0) // �����ε��¶�ֵС��E-6��ʱ������ʾ��ʾ����ļ�ͷ��
	{
		float distance = length(slopeDirection);
		float acosSlopeDirection = acos(slopeDirection.x/distance);	
		float slopeArrowsAngle = acosSlopeDirection;//�������ת��
		if(slopeDirection.y<0.0)//�ڶ���������
		{
			slopeArrowsAngle = 2.0 * PI - acosSlopeDirection;
		}
		//��Z����ת����ת����
		vec2 n = vec2(cos(slopeArrowsAngle),-sin(slopeArrowsAngle));
		vec2 t = vec2(sin(slopeArrowsAngle),cos(slopeArrowsAngle));
		mat2 slopeRotateZMatrix = mat2(n,t);
		//1������ת���Ƶ�(0.5,0.5)
		vec2 transCoord = limitTexCoord - vec2(0.5,0.5);
		//2����ԭ��Ϊ���ĵ���ת��������
		transCoord = slopeRotateZMatrix * transCoord ;
		//3������ת��(0.5,0.5)�Ƶ�ԭ�㴦
		transCoord += vec2(0.5,0.5);
		transCoord = smoothstep(0.0,1.0,transCoord);
		arrowsTexColor = texture2D(slopeArrowsTexture, transCoord);
		arrowAlpha = arrowsTexColor.a;
		// �������߽��к��ߵ�����
		float xNum = floor(transCoord.x * 64.0);
		float yNum = floor(transCoord.y * 64.0);
		if ((xNum<=2.0||xNum>=61.0||yNum<=2.0||yNum>=61.0)&&arrowAlpha<1.0)
		{
			arrowAlpha = 0.0;
		}
		arrowsTexColor = vec4(arrowsTexColor.rgb,arrowAlpha * slopeOpacity);
	}
	// ����ֵ
	vec4 texColor = texture2D(slopePolygonTexture, polygonTexCoord);
	if (texColor.r < 0.1)
	{
		discard;
		return;
	}
	if(slopeFillMode == 1)//���
	{
		finalColor = slopeFillColor;
	}
	else if(slopeFillMode == 2)//����
	{
		finalColor = arrowsTexColor;
	}
	else if(slopeFillMode == 3)//��������
	{
		finalColor = mix(slopeFillColor, arrowsTexColor, arrowAlpha);
	}

	gl_FragColor = finalColor;
}