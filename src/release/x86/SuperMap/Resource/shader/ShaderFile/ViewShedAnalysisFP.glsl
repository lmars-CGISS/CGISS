#if GL_ES
	precision highp float;
#endif

uniform sampler2D texture0;
uniform vec4 visibleAreaColor;
uniform vec4 hiddenAreaColor;
uniform mat4 textureViewMatrix;
uniform mat4 textureProjMatrix;
uniform float farDist;
uniform int isFloatTex;
uniform vec4 texture0_size;

varying vec4 renderTextureCoord;
varying vec4 viewPos;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

void main()
{
	// 计算最远距离的深度(在顶点着色器中计算后，插值到片元着色器中效果很差)
	vec4 texViewPos = textureViewMatrix * viewPos;
	texViewPos /= texViewPos.w;
	texViewPos.xyz *=  farDist / length(texViewPos.xyz);
	vec4 farPos = textureProjMatrix * texViewPos;
	float farDepth = farPos.z / farPos.w;
	farDepth = min(farDepth, 1.0);

	vec4 texCoord = renderTextureCoord / renderTextureCoord.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	texCoord.y = 1.0 - texCoord.y;
	if (texCoord.x<0.0 || texCoord.x>1.0
		|| texCoord.y<0.0 || texCoord.y>1.0
		|| texCoord.z<0.0 || texCoord.z>farDepth)
	{
		discard;
		return;
	}
	
	// 获取纹理中存储的深度值(从邻近的四个像素中取最大的深度)
	vec2 tcoord;
    tcoord.x = (texCoord.x * texture0_size.x) - 0.5;
    tcoord.y = (texCoord.y * texture0_size.y) - 0.5;
    float x0 = floor(tcoord.x);
    float x1 = ceil(tcoord.x);
    float y0 = floor(tcoord.y);
    float y1 = ceil(tcoord.y);
    // sample coordinates in [0,1]^2 domain
	vec2 invTexSize = vec2(1.0/texture0_size.x, 1.0/texture0_size.y);
    vec2 t00, t01, t10, t11;
    t00 = vec2((x0+0.5) * invTexSize.x, (y0+0.5) * invTexSize.y);
    t10 = vec2((x1+0.5) * invTexSize.x, (y0+0.5) * invTexSize.y);
    t01 = vec2((x0+0.5) * invTexSize.x, (y1+0.5) * invTexSize.y);
    t11 = vec2((x1+0.5) * invTexSize.x, (y1+0.5) * invTexSize.y);
    // grab the samples
    vec4 z00 = texture2D(texture0, t00);
    vec4 z01 = texture2D(texture0, t01);
    vec4 z10 = texture2D(texture0, t10);
    vec4 z11 = texture2D(texture0, t11);

	float depth = 1.0;
	if (isFloatTex == 1)
	{
		depth = max(max(z00.x, z01.x), max(z10.x, z11.x));
	}
	else
	{
		z00.x = unpackDepth(z00);
		z01.x = unpackDepth(z01);
		z10.x = unpackDepth(z10);
		z11.x = unpackDepth(z11);
		depth = max(max(z00.x, z01.x), max(z10.x, z11.x));
		depth = depth * 2.0 - 1.0;
	}
	
	// 边界模糊效果没有处理，后期再做
	float bias = 1.0e-6;
	float c = float(depth+bias < texCoord.z);
	vec4 resultColor = mix(visibleAreaColor, hiddenAreaColor, vec4(c));
	
	gl_FragColor = resultColor;
}
