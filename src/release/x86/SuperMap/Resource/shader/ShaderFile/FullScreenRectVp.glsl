// ����λ���ȵľ��λ��Ƶ�������Ļ����ɫ��
attribute vec4 vertex;
uniform vec4 viewport_size;

void main()
{
	// ��������任
	vec4 vVertex = vertex;
	vVertex.w = 1.0;
	vVertex.x = viewport_size.x * vVertex.x;
	vVertex.y = viewport_size.y * vVertex.y;
	vVertex.z = 0.0;
	gl_Position = vVertex;	
}
