#version 120

//gl_MultiTexCoord0.xy:  x������ʾ���������v���꣬y��ʾ���������߶ε�ǰ����һ�����棬0Ϊ�߶ε�ǰ���棬1Ϊ�߶εĺ����
//1,2,3�������������ʾǰ�����ģ�;���4,5,6�������������ʾ������ģ�;���
//gl_MultiTexCoord7.xy:  x����Ϊ������u�����������꣬y����Ϊǰ�����u������������

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

varying vec4 vec4SelectionColor;  // ѡ����ɫ
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

	// �����߶ε���Ļ����
	vec4 windowP0 = gl_ModelViewProjectionMatrix * worldPos0;
	vec4 windowP1 = gl_ModelViewProjectionMatrix * worldPos1;

	//��������Ļ�ռ����߶ε�����ͷ���
	vec2 dirInScreen = windowP1.xy - windowP0.xy;
    vec2 lineNormalInScreen = normalize(vec2(dirInScreen.y, -dirInScreen.x));
	
	//ȷ����ǰ���������߶��ϵ�ǰ���ĸ���
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

	//����Ļ�����ϼ���ָ���߿������ƫ����
	/*uv0.x�洢���ǹ��߽��涥���ں���淽���ϵ��������ꡣ��ʹ�������ɫ��ʱ������Ķ����Ǳʻ����˵Ķ��㣬���ǵ�v��������ֱ�Ϊ0��1������ô�����������Ϊ
	����ƫ��������
	viewport_size.z = 1/�ӿڿ��
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
