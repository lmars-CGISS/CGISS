//�ȸ��ߵ����ģʽ   1-ֻ�����ɫ  2-ֻ���Ƶȸ���  3-���Ƶȸ��߲������ɫ
uniform int contourFillMode;
uniform float contourInterval;
uniform vec4 lineColor;//�ȸ��ߵ���ɫ
uniform float opacity;
uniform float floor;
uniform float ceil;
uniform float maxVisibleAltitude;
uniform float minVisibleAltitude;
uniform vec4 selectAreaBound;//��ѡ���εı߽�
uniform vec4 tileBound;//��ѡ���εı߽�

uniform sampler2D texture0;
uniform sampler2D texture1;
#if POLYGON_TEXTURE
uniform sampler2D texture2;
#endif


varying float height;
varying vec4 texCoord;
varying vec4 oriTexCoord;
varying vec4 mixColor;

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

float computeMixCon()
{
	//�ȸ��ߺ͵Ǹ߷ֲ���ɫ
	float distanceToContour = mod(height-0.0002, contourInterval);
	float dxc = abs(dFdx(height));
	float dyc = abs(dFdy(height));
	float dF = max(dxc, dyc);
	return (distanceToContour < dF)?1.0:0.0;
}

vec4 computContourMapColor()
{
	float threshold = clamp(abs(ceil-floor),0.000001,20000.0);
	float contourRate = (height-floor)/threshold;
	float finalCoord = clamp(contourRate,0.0,1.0);
	vec2 contourCoord = vec2(0, finalCoord);
	return texture2D(texture1, contourCoord).rgba;
}

// �жϵ��Ƿ��ھ�����
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	// ������ɫ
	vec4 texColor = texture2D(texture0, texCoord.xy) * mixColor;
	if(height > maxVisibleAltitude || height < minVisibleAltitude || height < -9000.0)
	{
		gl_FragColor = texColor;
		return;
	}

#if POLYGON_TEXTURE
	vec2 polyTexCoord = oriTexCoord.xy;
	polyTexCoord.x = polyTexCoord.x * (tileBound.z - tileBound.x) + tileBound.x;
	polyTexCoord.y = (1.0 - polyTexCoord.y) * (tileBound.y - tileBound.w) + tileBound.w;

  	if(!isPointInRegion(polyTexCoord.xy, selectAreaBound))
  	{
		gl_FragColor = texColor;
  		return;
	}

	polyTexCoord.xy = polyTexCoord.xy - vec2(selectAreaBound.x, selectAreaBound.w);
	polyTexCoord.x = polyTexCoord.x / (selectAreaBound.z - selectAreaBound.x);
	polyTexCoord.y = 1.0 - polyTexCoord.y / (selectAreaBound.y - selectAreaBound.w);

	// ���������ֵ
	vec4 polyTexColor = texture2D(texture2, polyTexCoord.xy);

	if (polyTexColor.r < 0.1)
	{	
		gl_FragColor = texColor;
		return;
	}
#endif

	vec4 contourMapColor = vec4(0.0);
	float finalOpacity = opacity;
	if(contourFillMode == 1)
	{
		contourMapColor = computContourMapColor();
	}
	else if(contourFillMode == 2)
	{
		finalOpacity = computeMixCon();
		contourMapColor = lineColor;
	}
	else if(contourFillMode == 3)
	{
		float mix_con = computeMixCon();
		contourMapColor = mix(computContourMapColor(), lineColor, mix_con);
	}
	else
	{
		finalOpacity = 0.0;
	}
	vec4 finalColor = mix(texColor, contourMapColor, finalOpacity);
	gl_FragColor = finalColor;
}
