attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 colour;
attribute vec4 secondary_colour;
attribute vec4 uv0;
attribute vec4 uv1;

uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 inverse_projection_matrix;
uniform mat4 texture0_matrix;
uniform mat4 texture1_matrix;
uniform vec4 viewport_size;

//没有纹理只有颜色的点 需要用到这个参数
uniform vec4 surface_diffuse_colour;

varying vec4 vecVertexColor;
varying vec4 mixColor;
varying vec4 texCoord;
varying vec2 tex1Coord;

uniform float isFixedMaxSize;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

float computerOnePixelLength()
{
	// 计算投影后的坐标
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	vec4 winPos = projection_matrix * viewPos;
	
	// 偏移一个像素
	winPos.x -= 2.0 * viewport_size.z * winPos.w;
	
	// 变换回视觉坐标系
	vec4 newViewPos = inverse_projection_matrix * winPos;
	
	// 视觉坐标系中的偏差
	return length(viewPos - newViewPos);
}

// 计算经过视图投影变换的顶点坐标
vec4 computePos(vec3 vNormal)
{
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	viewPos.xyz += vNormal * computerOnePixelLength();
	// 向相机拉近一些
	viewPos.xyz *= 0.9;
	vec4 pos = projection_matrix * viewPos;
	return pos;
}

void main()
{
	// 计算纹理坐标
	texCoord = texture0_matrix * uv0;
	// 计算顶点坐标值
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	
	float fScale = 1.0;
	if(isFixedMaxSize > 0.9)
	{
		fScale = computerOnePixelLength();
	}
	fScale = fScale > 1.0 ? 1.0:fScale;
#if ICON
	viewPos.xyz += uv1.xyz * fScale;
#else
	tex1Coord = vec2(texture1_matrix * uv1);
	viewPos.xyz += normal.xyz * fScale;
#endif

	viewPos.xyz *= 0.9;
	gl_Position = projection_matrix * viewPos;

	vecVertexColor = secondary_colour;
	mixColor = colour * surface_diffuse_colour;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
