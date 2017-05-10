// �����ɫ���ʺ������֡��ر������̶����ش�С������

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 colour;
attribute vec4 secondary_colour;
attribute vec4 uv0;
attribute vec4 uv1;

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

varying vec4 vecVertexColor;
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

// ���㾭����ͼͶӰ�任�Ķ�������
vec4 computePos(vec3 vNormal)
{
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	viewPos.xyz += vNormal * computerOnePixelLength();
	// ���������һЩ
	viewPos.xyz *= 0.9;
	vec4 pos = projection_matrix * viewPos;
	return pos;
}

void main()
{
	// ������������
	texCoord = texture0_matrix * uv0;
	vecVertexColor = secondary_colour;
	mixColor = colour * surface_diffuse_colour;
#if ICON
	// ���㶥������ֵ
	gl_Position = computePos(uv1.xyz);
#else
	tex1Coord = vec2(texture1_matrix * uv1);
	// ���㶥������ֵ
	gl_Position = computePos(normal.xyz);
#endif

#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
