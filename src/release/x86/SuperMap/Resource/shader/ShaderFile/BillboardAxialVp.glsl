attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 uv0;

uniform mat4 view_matrix;
uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 texture0_matrix;
uniform vec4 surface_diffuse_colour;

varying vec4 mixColor;
varying vec4 texCoord;
#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void main()
{
	// 计算纹理坐标
	texCoord = texture0_matrix * uv0;
	
	// 构建视觉坐标系下的变换矩阵
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	vec4 origViewPos = view_matrix * vec4(0.0, 0.0, 0.0, 1.0);
	vec4 fixedAxis = viewPos - origViewPos;
	vec3 yAxis = normalize(fixedAxis.xyz);
	vec4 cameraViewPos = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 cameraViewVector = cameraViewPos - viewPos;
	vec3 zAxis = normalize(cameraViewVector.xyz);
	vec3 xAxis = normalize(cross(yAxis, zAxis));
	zAxis = cross(xAxis, yAxis);
	mat3 matrix = mat3(xAxis, yAxis, zAxis);
	
	// 计算顶点坐标值
	vec3 offset = normal.xzy;
	offset = matrix * offset;
	viewPos.xyz += offset.xyz;
	gl_Position = projection_matrix * viewPos;
	mixColor = surface_diffuse_colour;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
