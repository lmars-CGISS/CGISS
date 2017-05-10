// 将单位长度的矩形绘制到整个屏幕的着色器
attribute vec4 vertex;
uniform vec4 viewport_size;

void main()
{
	// 顶点坐标变换
	vec4 vVertex = vertex;
	vVertex.w = 1.0;
	vVertex.x = viewport_size.x * vVertex.x;
	vVertex.y = viewport_size.y * vVertex.y;
	vVertex.z = 0.0;
	gl_Position = vVertex;	
}
