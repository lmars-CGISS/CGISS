uniform vec4 selectAreaBound;//��ѡ���εı߽�
uniform float contourInterval;//�ȸ��ߵļ��
//�ȸ��ߵ����ģʽ   1-ֻ�����ɫ  2-ֻ���Ƶȸ���  3-���Ƶȸ��߲������ɫ
uniform int contourFillMode;
uniform vec4 lineColor;//�ȸ��ߵ���ɫ
uniform sampler2D contourColorTexture;
uniform float opacity;
uniform float floor;
uniform float ceil;
uniform float maxVisibleAltitude;
uniform float minVisibleAltitude;
uniform sampler2D contourPolygonTexture;

varying float height;
varying vec2 texCoord;

// �жϵ��Ƿ��ھ�����
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}

void main()
{
	// ����㲻�ڶ���ε����Bound��ʱ������������
	if (height > maxVisibleAltitude || height < minVisibleAltitude || !isPointInRegion(texCoord, selectAreaBound))
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
	// ����ֵ
	vec4 texColor = texture2D(contourPolygonTexture, polygonTexCoord);
	if (texColor.r < 0.1)
	{
		discard;
		return;
	}
	//�ȸ��ߺ͵Ǹ߷ֲ���ɫ
	float distanceToContour = mod(height-0.0002, contourInterval);
	float dxc = abs(dFdx(height));
	float dyc = abs(dFdy(height));
	float dF = max(dxc, dyc);
	float mix_con = (distanceToContour < dF)?1.0:0.0;

	float threshold = clamp(abs(ceil-floor),0.000001,20000.0);
	float contourRate = (height-floor)/threshold;
	float finalCoord = clamp(contourRate,0.0,1.0);
	vec2 contourCoord = vec2(0, finalCoord);
	vec3 contour = texture2D(contourColorTexture, contourCoord).rgb;
	vec4 contourColor = vec4(contour, opacity);

	vec4 finalColor = vec4(0.0);
	if(contourFillMode == 1)
	{
		finalColor = contourColor;
	}
	else if(contourFillMode == 2)
	{
		finalColor = vec4(lineColor.rgb, opacity * mix_con);
	}
	else if(contourFillMode == 3)
	{
		finalColor = mix(contourColor, vec4(lineColor.rgb,opacity), mix_con);
	}
	gl_FragColor = finalColor;
}