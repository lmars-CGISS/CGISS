// �����ɫ���ʺ������֡��ر������̶����ش�С������

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 uv0;
attribute vec4 uv1;

uniform mat4 view_matrix;
uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 inverse_projection_matrix;
uniform mat4 texture0_matrix;
uniform mat4 texture1_matrix;
uniform vec4 viewport_size;

//û������ֻ����ɫ�ĵ� ��Ҫ�õ��������
uniform vec4 surface_diffuse_colour;

varying vec4 texCoord;
varying vec2 tex1Coord;
varying vec4 mixColor;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

float computerOnePixelLength()
{
	// ����ͶӰ�������
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	vec4 winPos = projection_matrix * viewPos;
	
	// ƫ��һ������
	winPos.x -= 2.0 * viewport_size.z * winPos.w;
	
	// �任���Ӿ�����ϵ
	vec4 newViewPos = inverse_projection_matrix * winPos;
	
	// �Ӿ�����ϵ�е�ƫ��
	return length(viewPos - newViewPos);
}

void main()
{
	// ������������
	texCoord = texture0_matrix * uv0;
	tex1Coord = vec2(texture1_matrix * uv1);
	
	// �����Ӿ�����ϵ���������ֵ���ת����
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
		
	// ���㶥������ֵ
	vec3 offset = mat3(view_matrix) * normal;
	
	offset *= computerOnePixelLength();
	viewPos.xyz += offset;
	gl_Position = projection_matrix * viewPos;
	mixColor = surface_diffuse_colour;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
