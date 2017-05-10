// uv0.x�洢ѡ��״̬��0.0Ϊ��ѡ��,1.0Ϊѡ��
// uv1.xyz�洢�˶����������������������С�ͷ���
// uv2.xyz�洢�˶���ĺ������췽��
attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 secondary_colour;
attribute vec4 uv0;
attribute vec4 uv1;
attribute vec4 uv2; 

uniform mat4 worldviewproj_matrix;
uniform mat4 world_matrix;
uniform vec3 camera_position;
uniform vec4 surface_diffuse_colour;
uniform float lineWidth;

varying vec4 mixColor;
varying float fWindowZ;

#if SELECTION
uniform mat4 inverse_transpose_world_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform float fHitTestHeight; // ʰȡ��ĸ߶�
uniform float fGlobal; // �Ƿ������泡��0.0Ϊ����,1.0Ϊ��
varying vec4 vecVertexColor;
#endif

#if STENCIL_SELECTED
varying float fSelected;
#endif

#if COLOR_SELECTED
uniform vec4 selColor;
#endif

const float fTempScreen = 1236.077;

// ��ͶӰ�������Ƶ��Ӿ�����
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

// �����߿��
float ComputeLineWidth()
{
	vec4 worldPos = world_matrix * vec4(vertex.xyz, 1.0);
	return lineWidth * length(camera_position - worldPos.xyz) / fTempScreen;
}

void main()
{
#if SELECTION
	float shadowVolumeWidth = ComputeLineWidth();
	// ѡ��ʱ�ӿ�һЩ������ѡ��
	shadowVolumeWidth = shadowVolumeWidth * 3.0;

	vec4 worldPos = world_matrix * vec4(vertex.xyz, 1.0);
	// ������任���ر�
	if(fGlobal > 0.5)
	{
		worldPos.xyz = normalize(worldPos.xyz) * 6378137.0;
	}
	else
	{
		worldPos.z = 0.0;
	}

	vec4 worldNormal = inverse_transpose_world_matrix * vec4(normalize(uv1.xyz), 1.0);
	vec4 widthDir = inverse_transpose_world_matrix * vec4(uv2.xyz, 1.0);
	worldPos.xyz += worldNormal.xyz * fHitTestHeight + widthDir.xyz * shadowVolumeWidth;

	vec4 clip_pos =  projection_matrix * view_matrix * worldPos;
	gl_Position = depthClampFarPlane(clip_pos);
	vecVertexColor = secondary_colour;
#else
	float shadowVolumeWidth = ComputeLineWidth();
	vec4 vertexPos = vec4(vertex.xyz, 1.0);
	vertexPos.xyz = vertex.xyz + uv1.xyz + uv2.xyz * shadowVolumeWidth;
	vec4 clip_pos = worldviewproj_matrix * vertexPos;
	mixColor = colour * surface_diffuse_colour;
	gl_Position = depthClampFarPlane(clip_pos);

#if STENCIL_SELECTED
	fSelected = uv0.x;
#endif

#if COLOR_SELECTED
	mixColor = selColor;
#endif

#endif
}

