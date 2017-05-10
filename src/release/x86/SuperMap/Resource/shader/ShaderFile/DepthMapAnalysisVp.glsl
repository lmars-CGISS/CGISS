
uniform mat4 renderTextureMatrix;
varying vec4 renderTextureCoord;
varying float texCoordX;

void main()
{
	// 投影到屏幕上的位置
	gl_Position = ftransform();

	// 计算灯光空间下的顶点位置
	// 直接算出世界坐标会导致精度损失（坐标值太大导致float截取）; 
	// 通过先求视觉坐标，再与外面计算好的矩阵相乘，避免着色器中出现太大的值
	vec4 viewPos = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	renderTextureCoord = renderTextureMatrix * viewPos;
	texCoordX = gl_MultiTexCoord0.x;
}
