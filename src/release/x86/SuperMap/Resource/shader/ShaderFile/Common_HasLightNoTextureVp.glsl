
attribute vec4 vertex;
attribute vec3 normal;

#if ADDTEX
attribute vec4 uv0;
#endif

uniform mat4 worldviewproj_matrix;
uniform mat4 worldview_matrix;

#if ADDTEX
uniform mat4 texture0_matrix;
#endif

uniform vec3 light_direction_view_space;
uniform vec4 ambient_light_colour;
uniform vec4 light_diffuse_colour;
uniform vec4 light_specular_colour;
uniform vec4 surface_ambient_colour;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;

#if ADDTEX
varying vec4 texCoord;
#endif

varying vec4 mixColor;
varying vec4 clip_pos;
varying float fWindowZ;
#if SCISSOR_TEST
varying vec4 vPosition;
#endif

#if CLIP
varying vec4 clip_vertex;
#endif

// ��ͶӰ�������Ƶ��Ӿ�����
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

void directionalLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	vec3 ecPosition = vec3(worldview_matrix * vec4(vertex.xyz, 1.0));

	// ����ӱ���㵽�����������
	//vec3 eye = normalize(cameraPos-ecPosition);
	vec3 eye = -normalize(ecPosition);
	vec3 vp = -normalize(light_direction_view_space);
	// ������������ߵİ�����
	vec3 halfVector = normalize(vp+eye);
	
	float nDotVP = max(0.0, dot(normal, vp));
	float nDotHV = dot(normal, halfVector);

	// �ֲڶȣ�ԽСԽ�⻬
	float shininess = 50.0;//gl_FrontMaterial.shininess;
	// ���淴���ǿ������
	float powerFactor = max(0.0, pow(nDotHV, shininess));

	ambient += ambient_light_colour;
	diffuse += light_diffuse_colour * nDotVP;
	specular += light_specular_colour * powerFactor;
}

void main()
{
	// ���㶨����ͨ��ǿ��
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);

	//vec3 normalTarget = vertex.xyz + normal;
	//vec3 newNormal = (worldview_matrix*vec4(normalTarget, 1)).xyz
	//	- (worldview_matrix*vec4(vertex.xyz, 1.0)).xyz;
	vec3 newNormal = vec3(worldview_matrix*vec4(normal, 0.0));
	newNormal = normalize(newNormal);
	
	directionalLight(newNormal, ambientTemp, diffuseTemp, specularTemp);
	mixColor = ambientTemp*surface_ambient_colour
		+ diffuseTemp*surface_diffuse_colour
		+ specularTemp*surface_specular_colour;

#if ADDTEX
	// ��������任
	texCoord.xyz = vec3(texture0_matrix * uv0);
#endif

	// ��������任
	clip_pos = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
	gl_Position = depthClampFarPlane(clip_pos);

#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

#if CLIP
	clip_vertex = worldview_matrix * vec4(vertex.xyz, 1.0);
#endif

	// Ĭ�ϵ��С��Ϊ 10
	gl_PointSize = 10.0;
}
