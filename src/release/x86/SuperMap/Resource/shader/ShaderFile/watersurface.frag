uniform float Time;
uniform sampler2D WaveTexture;
uniform sampler2D BumpMap;
uniform sampler2D BoundaryMap;
uniform sampler2D ChinaBoundaryMap;
uniform sampler2D RegionBoundaryMap;
uniform sampler2D SprayMap;

uniform int bHasRegionBdyTexture; 
uniform int TexWidth;
uniform int TexHeight;

uniform int bHasSprayTexture;

varying vec3  ViewVec;
varying vec4 v_color;
varying vec2 bumpCoord0;

varying vec3 LightDir;
varying float specPow;
varying float factor;//反光因子

const float PI = 3.14159;
const int NWAVES = 4;		// 波的数量

// 定义波的结构
struct Wave {
  float freq;  // 角频率=2*PI/wavelength	
  float amp;   // 振幅
  float phase; // 相常数=speed*2*PI/wavelength
  vec2 dir;	   // 方向
  float q;
};
Wave wave[NWAVES];

// 初始化各个波
void InitWaves()
{
	wave[0].freq =  2.0 * PI / 0.33;
	wave[0].amp = 0.0033;
	wave[0].phase = 0.0002 * 2.0 * PI / 0.33;
	wave[0].dir = vec2(0.966, -0.259);
	wave[0].q = 0.5;

	wave[1].freq =  2.0 * PI / 0.25;
	wave[1].amp = 0.0125;
	wave[1].phase = 0.0003 * 2.0 * PI / 0.25;
	wave[1].dir = vec2(0.707, -0.707);
	wave[1].q = 0.5;

	wave[2].freq =  2.0 * PI / 0.1;
	wave[2].amp = 0.005;
	wave[2].phase = 0.0005 * 2.0 * PI / 0.1;
	wave[2].dir = vec2(0.259, -0.966);
	wave[2].q = 0.5;

	wave[3].freq =  2.0 * PI / 0.05;
	wave[3].amp = 0.0025;
	wave[3].phase = 0.001 * 2.0 * PI / 0.05;
	wave[3].dir = vec2(0.707, -0.707);
	wave[3].q = 0.5;
}

// 计算波的副法线向量
vec3 waveBinormal(vec2 p)
{
	float dx = 0.0, dy = 0.0, dz = 0.0;
	float WA, S, C;

 	for(int i = 0; i < NWAVES; i++)
 	{
 		WA = wave[i].freq * wave[i].amp;
 		S = sin(wave[i].freq * dot(wave[i].dir, p) + wave[i].phase * Time);
 		C = cos(wave[i].freq * dot(wave[i].dir, p) + wave[i].phase * Time);
 
 		dx += wave[i].q * wave[i].dir.x * wave[i].dir.x * WA * S;
 		dy += wave[i].q * wave[i].dir.x * wave[i].dir.y * WA * S;
 		dz += wave[i].dir.x * WA * C;
 	}

	return normalize(vec3(1.0-dx, -dy, dz));
}

// 计算波的切线向量
vec3 waveTangent(vec2 p)
{
	float dx = 0.0, dy = 0.0, dz = 0.0;
	float WA, S, C;

	for(int i = 0; i < NWAVES; i++)
	{
		WA = wave[i].freq * wave[i].amp;
		S = sin(wave[i].freq * dot(wave[i].dir, p) + wave[i].phase * Time);
		C = cos(wave[i].freq * dot(wave[i].dir, p) + wave[i].phase * Time);

		dx += wave[i].q * wave[i].dir.x * wave[i].dir.y * WA * S;
		dy += wave[i].q * wave[i].dir.y * wave[i].dir.y * WA * S;
		dz += wave[i].dir.y * WA * C;
	}

	return normalize(vec3(-dx, 1.0-dy, dz));
}
 
void main(void)
{
	// 初始化各个波
	InitWaves();
	vec4 color = v_color;
	vec4 boundary = texture2D( BoundaryMap, gl_TexCoord[2].xy );
	vec2 texChinaOffset = vec2(0.5 / 2048.0, 0.5 / 2048.0);
	//中国区域边界纹理, 此处加上0.5/2048.0 是因为纹理坐标对应的像素坐标有偏差, 下同
	vec2 chinaTexCoords = vec2(gl_TexCoord[3].s + texChinaOffset.x, gl_TexCoord[3].t + texChinaOffset.y);
	vec4 chinaBoundaryColor = texture2D( ChinaBoundaryMap, chinaTexCoords );

	vec4 regionBoundaryColor;
	bool bExistRegionTex = bool(bHasRegionBdyTexture);
	
	vec2 texRegionOffset;
	if (bExistRegionTex)
	{	
		if(TexWidth != 0 && TexHeight != 0)
		{
			texRegionOffset.x = 0.5 / float(TexWidth);
			texRegionOffset.y = 0.5 / float(TexHeight);
		}
	
		//局部(精细)边界纹理
		vec2 regionTexCoors = vec2(gl_TexCoord[4].s + texRegionOffset.x, gl_TexCoord[4].t + texRegionOffset.y);
		regionBoundaryColor = texture2D( RegionBoundaryMap, regionTexCoors );	
	}
	
	if(boundary.a + regionBoundaryColor.a + chinaBoundaryColor.a < 0.00001)
	{
		discard;
		return;
	}
	
	vec4 vBaseColor = texture2D(WaveTexture, gl_TexCoord[0].st)/*vec4(0.0, 0.2, 0.4, 1.0)*/;
 
	// 计算正弦波的法线方向
	vec3 B, T, N;
	B = waveBinormal(gl_TexCoord[0].st);
	T = waveTangent(gl_TexCoord[0].st);
	N = cross(B, T);
	mat3 trans = mat3(B, T, N);

	vec3 vBumpColor0 = vec3(texture2D(BumpMap, bumpCoord0.st));
	vec3 vBumpColor1 = vec3(texture2D(BumpMap, 1.8 * bumpCoord0.st));
	vec3 vBumpColor2 = vec3(texture2D(BumpMap, 3.1 * bumpCoord0.st));
	//vBumpColor = vBumpColor * 2 - 1;

	vec3 vBumpColor = vBumpColor0 + vBumpColor1 + vBumpColor2;
	vBumpColor.rg *= 0.5;
	vBumpColor = normalize(vBumpColor);

	vec3 vNormal = normalize(vBumpColor * trans);

	// 凹凸贴图的计算
	color.rgb = vBaseColor.rgb * max(dot(vNormal, LightDir), 0.0);
	vec3 reflectDir = reflect(LightDir, vNormal); 
	float spec = max(dot(ViewVec, reflectDir), 0.0);
	spec = pow(spec, specPow);
	spec *= 0.5;
	color = min(color + spec, vec4(1.0));
	
	 if(factor > 1.0)
    {
		//模糊处理，防止远处的回形波
		color.rgb = color.rgb * (1.0 / factor) + (1 - 1.0 / factor) * vec3(0.1255, 0.1922, 0.2941);
    }
    
	texRegionOffset *= 4.0;
	texChinaOffset *= 4.0;

	// 如果有船走过后的浪花
	if (bHasSprayTexture == 1)
	{
		vec2 sprayUV = vec2(gl_TexCoord[4].s+texChinaOffset.x, gl_TexCoord[4].t+texChinaOffset.y);
		sprayUV.s = sprayUV.s - 0.4;
		sprayUV.t = sprayUV.t + 0.5;
		if (sprayUV.s < 1.0 && sprayUV.s > 0.0 && sprayUV.t < 1.0 && sprayUV.t > 0.0)
		{
			vec4 sprayColor = texture2D(SprayMap, sprayUV);
			color = mix(color, vec4(0.8, 0.8, 0.9, 1.0), sprayColor.a);
		}
	}
	
    //如果有局部清晰纹理并且当前海洋位于其范围内，则使用其alpha值
    if(bExistRegionTex && gl_TexCoord[4].s < 1.0 - texRegionOffset.x && gl_TexCoord[4].t < 1.0 - texRegionOffset.y &&
    gl_TexCoord[4].s > 0.0 + texRegionOffset.x && gl_TexCoord[4].t > 0.0 + texRegionOffset.y)
    {
		color.w *= regionBoundaryColor.a;
    }
    else if(gl_TexCoord[3].s < 1.0 - texChinaOffset.x && gl_TexCoord[3].t < 1.0 - texChinaOffset.y &&
		gl_TexCoord[3].s > 0.0 + texChinaOffset.x && gl_TexCoord[3].t > 0.0 + texChinaOffset.y)
    {
		color.w *= chinaBoundaryColor.a;	//精细边界范围内使用精细边界的alpha
    }
	else
	{
 		color.w *= boundary.a;		// 非海洋部分全透明
 	}

	gl_FragColor = color;
}