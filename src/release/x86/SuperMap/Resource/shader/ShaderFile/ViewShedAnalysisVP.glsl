attribute vec4 vertex;

uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 renderTextureMatrix;

varying vec4 renderTextureCoord;
varying vec4 viewPos;

void main()
{
	// 计算灯光空间下的顶点位置
	// 直接算出世界坐标会导致精度损失（坐标值太大导致float截取）; 
	// 通过先求视觉坐标，再与外面计算好的矩阵相乘，避免着色器中出现太大的值
	viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	renderTextureCoord = renderTextureMatrix * viewPos;
	
	// project position to the screen
	gl_Position = projection_matrix * viewPos;

#if !GL_ES
	gl_ClipVertex = worldview_matrix * vec4(vertex.xyz, 1.0);
#endif
}
