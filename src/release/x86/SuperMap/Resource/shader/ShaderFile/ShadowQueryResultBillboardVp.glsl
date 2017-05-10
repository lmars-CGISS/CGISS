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
	// ��������
	tex0Coord = vec2(texture0_matrix * uv0);

	// ����ƹ�ռ��µĶ���λ��
	// ֱ�������������ᵼ�¾�����ʧ������ֵ̫����float��ȡ��; 
	// ͨ�������Ӿ����꣬�����������õľ�����ˣ�������ɫ���г���̫���ֵ
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	renderTextureCoord = renderTextureMatrix * (view_matrix_T * vec4(vertex.xyz, 1.0));
	
	// ����ƫ�ƺ��λ��
	viewPos.xyz += normal;
	gl_Position = projection_matrix * viewPos;
}
