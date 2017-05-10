attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 uv0;
attribute vec4 uv1;

uniform mat4 texture0_matrix;
uniform mat4 texture1_matrix;
uniform vec4 viewport_size;

//没有纹理只有颜色时 需要用到这个参数
uniform vec4 surface_diffuse_colour;
varying vec4 mixColor;

varying vec4 texCoord;
varying vec2 tex1Coord;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void main()
{
	// 计算纹理坐标
	texCoord = texture0_matrix * uv0;
	tex1Coord = vec2((texture1_matrix * uv1).xy);

	// 计算顶点坐标值
	vec3 screenPos = vertex.xyz;
	screenPos += normal;
	screenPos.xy *= viewport_size.zw;
	screenPos.xy = screenPos.xy*2.0 - 1.0;
	gl_Position = vec4(screenPos, 1.0);
	mixColor = surface_diffuse_colour;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}