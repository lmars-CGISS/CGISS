attribute vec4 vertex;

uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 renderTextureMatrix;

varying vec4 renderTextureCoord;
varying vec4 viewPos;

void main()
{
	// ����ƹ�ռ��µĶ���λ��
	// ֱ�������������ᵼ�¾�����ʧ������ֵ̫����float��ȡ��; 
	// ͨ�������Ӿ����꣬�����������õľ�����ˣ�������ɫ���г���̫���ֵ
	viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	renderTextureCoord = renderTextureMatrix * viewPos;
	
	// project position to the screen
	gl_Position = projection_matrix * viewPos;

#if !GL_ES
	gl_ClipVertex = worldview_matrix * vec4(vertex.xyz, 1.0);
#endif
}
