#version 120

//gl_MultiTexCoord0.xy:  x分量表示顶点的纹理v坐标，y表示顶点属于线段的前后哪一个截面，0为线段的前截面，1为线段的后截面
//1,2,3三重纹理坐标表示前截面的模型矩阵，4,5,6三重纹理坐标表示后截面的模型矩阵，
//gl_MultiTexCoord7.xy:  x分量为后截面的u方向纹理坐标，y分量为前截面的u方向纹理坐标

//Parameters
uniform vec4 viewport_size;
uniform sampler2D selectionTexture;
uniform mat4 texture0_matrix;

attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2;
attribute vec4 uv3;
attribute vec4 uv4;
attribute vec4 uv5;
attribute vec4 uv6;
attribute vec4 uv7;

varying vec4 vec4SelectionColor;  // 选中颜色
varying vec4 texCoord;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void main(void)
{
	mat4 worldMatrix0;
	mat4 worldMatrix1;

	worldMatrix0[0] = uv1;
	worldMatrix0[1] = uv2;
	worldMatrix0[2] = uv3;
	worldMatrix0[3] = vec4( 0, 0, 0, 1 );

	worldMatrix1[0] = uv4;
	worldMatrix1[1] = uv5;
	worldMatrix1[2] = uv6;
	worldMatrix1[3] = vec4( 0, 0, 0, 1 );

	vec4 worldPos0 = vec4(vertex.xyz, 1.0) * worldMatrix0;
	vec4 worldPos1 = vec4(vertex.xyz, 1.0) * worldMatrix1;

	// 计算线段的屏幕坐标
	vec4 windowP0 = gl_ModelViewProjectionMatrix * worldPos0;
	vec4 windowP1 = gl_ModelViewProjectionMatrix * worldPos1;

	//计算在屏幕空间中线段的走向和法线
	vec2 dirInScreen = windowP1.xy - windowP0.xy;
    vec2 lineNormalInScreen = normalize(vec2(dirInScreen.y, -dirInScreen.x));
	
	//确定当前顶点属于线段上的前后哪个点
	vec4 windowPos;
	vec4 worldPos;
	if(uv0.y > 0.5)
	{
		windowPos = windowP1;
		worldPos = worldPos1;
		texCoord = texture0_matrix * vec4(uv7.x, uv0.x, 0.0, 1.0);
	}
	else
	{
		windowPos = windowP0;
		worldPos = worldPos0;
		texCoord = texture0_matrix * vec4(uv7.y, uv0.x, 0.0, 1.0);
	}

	//在屏幕坐标上加上指定线宽的像素偏移量
	/*uv0.x存储的是管线截面顶点在横截面方向上的纹理坐标。当使用这个着色器时，传入的顶点是笔画两端的顶点，它们的v纹理坐标分别为0和1，因此用此纹理坐标作为
	像素偏移量基数
	viewport_size.z = 1/视口宽度
	*/
	float width = 3;
	windowPos.xy += lineNormalInScreen * width * (uv0.x - 0.5) * 2.0 * viewport_size.z * windowPos.w;
	gl_Position = windowPos;
	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

	vec4 viewPos = gl_ModelViewMatrix * worldPos;
	gl_ClipVertex = viewPos;

	gl_FrontColor = colour;
	vec4SelectionColor = vec4(1.0, 1.0, 1.0, 1.0);
}
