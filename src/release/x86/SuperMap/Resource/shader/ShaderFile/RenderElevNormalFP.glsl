uniform sampler2D elevationTexture;
// 传入纹理边界
uniform vec4 elevBounds;
// 是否是平面场景 0:平面场景，1：球面场景
uniform int isEarth;

const float step = 0.001953125;

const float fPlanetRadius = 6378137.0;	// 地球半径

//计算当前相邻梯度采样点之间的实际距离
vec2 ComputeRealStep()
{
	vec2 realStep = vec2(0.0);
	//经度方向上当前层的跨度
	float dLongSpan = elevBounds.z - elevBounds.x;
	//纬度方向上当前层的跨度
	float dLatSpan = elevBounds.y - elevBounds.w;
	
	realStep.x = dLongSpan * step;
	realStep.y = dLatSpan * step;
	if (isEarth == 1)
	{
		//根据纹理坐标求出纬度
		float dLat = elevBounds.w + dLatSpan * (1.0 - gl_TexCoord[0].y);
		//当前纬度上对应的小圆半径
		float fRadius = fPlanetRadius * cos(dLat);
		//计算一个经度step对应的长度
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