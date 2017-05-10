attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 uv0;

uniform mat4 worldview_matrix;
uniform mat4 world_matrix;
uniform mat4 projection_matrix;
uniform mat4 view_matrix_T;
uniform mat4 texture0_matrix;
uniform mat4 renderTextureMatrix;

varying vec4 renderTextureCoord;
varying vec2 tex0Coord;

void main()
{
	// 纹理坐标
	tex0Coord = vec2(texture0_matrix * uv0);

	// 计算灯光空间下的顶点位置
	// 直接算出世界坐标会导致精度损失（坐标值太大导致float截取）; 
	// 通过先求视觉坐标，再与外面计算好的矩阵相乘，避免着色器中出现太大的值
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	renderTextureCoord = renderTextureMatrix * (view_matrix_T * vec4(vertex.xyz, 1.0));
	
	// 计算偏移后的位置
	viewPos.xyz += normal;
	gl_Position = projection_matrix * viewPos;
}
