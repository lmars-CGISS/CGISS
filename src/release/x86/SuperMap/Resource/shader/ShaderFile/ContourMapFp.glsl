uniform vec4 selectAreaBound;//框选矩形的边界
uniform float contourInterval;//等高线的间隔
//等高线的填充模式   1-只填充颜色  2-只绘制等高线  3-绘制等高线并填充颜色
uniform int contourFillMode;
uniform vec4 lineColor;//等高线的颜色
uniform sampler2D contourColorTexture;
uniform float opacity;
uniform float floor;
uniform float ceil;
uniform float maxVisibleAltitude;
uniform float minVisibleAltitude;
uniform sampler2D contourPolygonTexture;

varying float height;
varying vec2 texCoord;

// 判断点是否在矩形内
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}

void main()
{
	// 如果点不在多边形的外接Bound内时，丢弃并返回
	if (height > maxVisibleAltitude || height < minVisibleAltitude || !isPointInRegion(texCoord, selectAreaBound))
	{
		discard;
		return;
	}

	// 把多边形的Bound的左下点的纹理坐标变换为(0.0,0.0)
	vec2 polygonTexCoord = texCoord - vec2(selectAreaBound.x, selectAreaBound.w);
	// 小纹理的在x,y方向的缩放比例
	float xScale = 1.0 / (selectAreaBound.z - selectAreaBound.x);
	float yScale = 1.0 / (selectAreaBound.y - selectAreaBound.w);
	// 把小纹理的纹理坐标的值变换到0~1之间。
	polygonTexCoord.x = polygonTexCoord.x * xScale;
	polygonTexCoord.y = polygonTexCoord.y * yScale;
	// 纹理值
	vec4 texColor = texture2D(contourPolygonTexture, polygonTexCoord);
	if (texColor.r < 0.1)
	{
		discard;
		return;
	}
	//等高线和登高分层设色
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