// 这个着色器适合像文字、地标这样固定像素大小的物体

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 uv0;
attribute vec4 uv1;

uniform mat4 view_matrix;
uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 inverse_projection_matrix;
uniform mat4 texture0_matrix;
uniform mat4 texture1_matrix;
uniform vec4 viewport_size;

//没有纹理只有颜色的点 需要用到这个参数
uniform vec4 surface_diffuse_colour;
varying vec4 mixColor;

varying vec4 texCoord;
varying vec2 tex1Coord;

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

void main()
{
	// 计算纹理坐标
	texCoord = texture0_matrix * uv0;
	tex1Coord = vec2(texture1_matrix * uv1);
	
	// 构建视觉坐标系下贴地文字的旋转矩阵
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	vec4 origViewPos = view_matrix * vec4(0.0, 0.0, 0.0, 1.0);
	vec4 fixedAxis = viewPos - origViewPos;
	vec3 zAxis = normalize(fixedAxis.xyz);
	vec4 upViewPos = view_matrix * vec4(0.0, 1.0, 0.0, 1.0);
	vec3 upViewVector = normalize(vec3(upViewPos - origViewPos));
	vec3 xAxis = normalize(cross(upViewVector, zAxis));
	vec3 yAxis = cross(zAxis, xAxis);
	mat3 matrix = mat3(xAxis, yAxis, zAxis);
	
	// 绕z轴旋转指定角度的矩阵
	float angle = uv0.z;
	float sina = sin(angle);
	float cosa = cos(angle);
	mat3 rotMatrix = mat3(cosa, sina, 0, -sina, cosa, 0, 0, 0, 1);
	
	// 计算顶点坐标值
	vec3 offset = normal;
	offset = rotMatrix * offset;
	offset = matrix * offset;
	offset *= computerOnePixelLength();
	viewPos.xyz += offset;
	gl_Position = projection_matrix * viewPos;
	mixColor = surface_diffuse_colour;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
