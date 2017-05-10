
uniform mat4 renderTextureMatrix;
varying vec4 renderTextureCoord;
varying float texCoordX;

void main()
{
	// ͶӰ����Ļ�ϵ�λ��
	gl_Position = ftransform();

	// ����ƹ�ռ��µĶ���λ��
	// ֱ�������������ᵼ�¾�����ʧ������ֵ̫����float��ȡ��; 
	// ͨ�������Ӿ����꣬�����������õľ�����ˣ�������ɫ���г���̫���ֵ
	vec4 viewPos = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	renderTextureCoord = renderTextureMatrix * viewPos;
	texCoordX = gl_MultiTexCoord0.x;
}
