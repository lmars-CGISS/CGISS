uniform sampler2D slopeColorTexture;
uniform sampler2D slopeArrowsTexture;
uniform vec4 selectAreaBound;//框选矩形的边界
uniform int slopeFillMode;//坡度、坡向的显示模式
uniform float slopeOpacity;//透明度
uniform float floorAngle;
uniform float ceilAngle;
uniform float maxVisibleSlope;
uniform float minVisibleSlope;
uniform sampler2D slopePolygonTexture;

varying vec2 texCoord;
varying vec3 realNormal;
varying vec2 texCoordRotate;
const float PI = 3.1415926535897932384626;
// 判断点是否在矩形内
bool isPointInRegion(vec2 point, vec4 region)
{
	return (point.x>region.x && point.x<region.z
		&& point.y<region.y && point.y>region.w);
}
void main()
{
	// 如果点不在多边形的外接Bound内时，丢弃并返回
	if (!isPointInRegion(texCoord, selectAreaBound))
	{
		discard;
		return;
	}
	// 计算地形坡度值
	float slopeRate = abs(normalize(realNormal).z);

	float slopeAngle = acos(slopeRate);
	//当坡度不在分析范围时，返回
	if (slopeAngle < minVisibleSlope || slopeAngle > maxVisibleSlope)
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
	//坡度阈值
	float threshold = clamp(abs(ceilAngle-floorAngle),0.0000001,PI/2.0);
	float rate = (slopeAngle-floorAngle)/threshold;
	float finalRate = clamp(rate,0.0,1.0);
	vec2 slopeCoord = vec2(0, finalRate);
	vec4 slope = texture2D(slopeColorTexture, slopeCoord);	
	vec4 finalColor = vec4(0.0);
	vec4 slopeFillColor = vec4(slope.xyz, slopeOpacity);
	//坡向	  把纹理坐标限定在(0.0,1.0)间
	vec2 limitTexCoord = fract(texCoordRotate);
	//地形的法线在XY平面上的投影
	vec2 slopeDirection = realNormal.xy;
	vec4 arrowsTexColor = vec4(0.0);
	float arrowAlpha = 0.0;
	//当slopeDirection为0时，表示一个没有起伏的平面,不绘制坡向
	if (slopeAngle>PI/180.0) // 当地形的坡度值小于E-6度时，不显示表示方向的箭头。
	{
		float distance = length(slopeDirection);
		float acosSlopeDirection = acos(slopeDirection.x/distance);	
		float slopeArrowsAngle = acosSlopeDirection;//坡向的旋转角
		if(slopeDirection.y<0.0)//第二、三象限
		{
			slopeArrowsAngle = 2.0 * PI - acosSlopeDirection;
		}
		//绕Z轴旋转的旋转矩阵
		vec2 n = vec2(cos(slopeArrowsAngle),-sin(slopeArrowsAngle));
		vec2 t = vec2(sin(slopeArrowsAngle),cos(slopeArrowsAngle));
		mat2 slopeRotateZMatrix = mat2(n,t);
		//1、把旋转点移到(0.5,0.5)
		vec2 transCoord = limitTexCoord - vec2(0.5,0.5);
		//2、以原点为中心点旋转纹理坐标
		transCoord = slopeRotateZMatrix * transCoord ;
		//3、把旋转点(0.5,0.5)移到原点处
		transCoord += vec2(0.5,0.5);
		transCoord = smoothstep(0.0,1.0,transCoord);
		arrowsTexColor = texture2D(slopeArrowsTexture, transCoord);
		arrowAlpha = arrowsTexColor.a;
		// 解决坡向边界有黑线的问题
		float xNum = floor(transCoord.x * 64.0);
		float yNum = floor(transCoord.y * 64.0);
		if ((xNum<=2.0||xNum>=61.0||yNum<=2.0||yNum>=61.0)&&arrowAlpha<1.0)
		{
			arrowAlpha = 0.0;
		}
		arrowsTexColor = vec4(arrowsTexColor.rgb,arrowAlpha * slopeOpacity);
	}
	// 纹理值
	vec4 texColor = texture2D(slopePolygonTexture, polygonTexCoord);
	if (texColor.r < 0.1)
	{
		discard;
		return;
	}
	if(slopeFillMode == 1)//填充
	{
		finalColor = slopeFillColor;
	}
	else if(slopeFillMode == 2)//坡向
	{
		finalColor = arrowsTexColor;
	}
	else if(slopeFillMode == 3)//填充和坡向
	{
		finalColor = mix(slopeFillColor, arrowsTexColor, arrowAlpha);
	}

	gl_FragColor = finalColor;
}