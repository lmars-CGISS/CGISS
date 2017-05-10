// uv0.x�洢ѡ��״̬��0.0Ϊ��ѡ��,1.0Ϊѡ��
// uv1.xyz�洢�˶����������������������С�ͷ���
attribute vec4 vertex;
attribute vec4 colour;
attribute vec4 secondary_colour;
attribute vec4 uv0;
attribute vec4 uv1;

uniform mat4 worldviewproj_matrix;
uniform mat4 world_matrix;
uniform vec4 surface_diffuse_colour;

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

const float fGlobalRadius = 6378137.0;

// ��ͶӰ�������Ƶ��Ӿ�����
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

// ���������������ѡ��Pass�Ķ���任
void VertexTransformForExtendObjectSelection(float fHitTestHeight, float fGlobal, mat4 worldMatrix, mat4 viewMatrix, mat4 projMatrix, mat4 worldviewprojMatrix)
{
	float fExtendHeight = fHitTestHeight;
	vec4 worldPos = worldMatrix * vec4(vertex.xyz, 1.0);
	vec4 height0Pos = worldPos;
	float bottomHeight = length(worldPos.xyz);
	// ������任���ر�
	if(fGlobal > 0.5)
	{
		height0Pos.xyz = normalize(worldPos.xyz) * fGlobalRadius;
		bottomHeight -= fGlobalRadius;
	}
	else
	{
		height0Pos.z = 0.0;
	}
	float topHeight = bottomHeight + length(uv1.xyz);
	//���涥��
	if(length(uv1.xyz) < 0.01)
	{
		vec4 clip_pos = projMatrix * viewMatrix * height0Pos;
		gl_Position = depthClampFarPlane(clip_pos);
	}
	else
	{
		// �߶���ʰȡ��Χ��
		if(fHitTestHeight > bottomHeight && fHitTestHeight < topHeight)
		{
			vec4 vertexPos = vec4(vertex.xyz, 1.0);
			vertexPos.xyz = vertexPos.xyz + uv1.xyz;
			vec4 clip_pos = worldviewprojMatrix * vertexPos;
			gl_Position = depthClampFarPlane(clip_pos);
		}
		else
		{
			vec4 clip_pos = projMatrix * viewMatrix * height0Pos;
			gl_Position = depthClampFarPlane(clip_pos);
		}
	}
}

// ��ѡ��Pass�Ķ���任
void VertexTransformForSelection(float fHitTestHeight, float fGlobal, mat4 worldMatrix, mat4 viewMatrix, mat4 projMatrix, mat4 inverseTransposeWorldMatrix)
{
	float fExtendHeight = fHitTestHeight;
	vec4 worldPos = worldMatrix * vec4(vertex.xyz, 1.0);
	// ������任���ر�
	if(fGlobal > 0.5)
	{
		worldPos.xyz = normalize(worldPos.xyz) * fGlobalRadius;
	}
	else
	{
		worldPos.z = 0.0;
	}
	vec4 worldNormal = inverseTransposeWorldMatrix * vec4(normalize(uv1.xyz), 1.0);
	worldPos.xyz += worldNormal.xyz * fExtendHeight;
	vec4 clip_pos = projMatrix * viewMatrix * worldPos;
	gl_Position = depthClampFarPlane(clip_pos);
}

void main()
{
#if SELECTION
#if EXTEND_OBJECT
	VertexTransformForExtendObjectSelection(fHitTestHeight, fGlobal, world_matrix, view_matrix, projection_matrix, worldviewproj_matrix);
#else
	VertexTransformForSelection(fHitTestHeight, fGlobal, world_matrix, view_matrix, projection_matrix, inverse_transpose_world_matrix);
#endif
	vecVertexColor = secondary_colour;
#else
	vec4 vertexPos = vec4(vertex.xyz, 1.0);
	vertexPos.xyz = vertexPos.xyz + uv1.xyz;
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

