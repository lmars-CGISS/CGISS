// uv0.x存储选中状态，0.0为非选中,1.0为选中
// uv1.xyz存储了顶点的纵向拉伸量，包括大小和方向
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
uniform float fHitTestHeight; // 拾取点的高度
uniform float fGlobal; // 是否是球面场景0.0为不是,1.0为是
varying vec4 vecVertexColor;
#endif

#if STENCIL_SELECTED
varying float fSelected;
#endif

#if COLOR_SELECTED
uniform vec4 selColor;
#endif

const float fGlobalRadius = 6378137.0;

// 将投影后坐标移到视景体内
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

// 对贴对象拉伸对象选择Pass的顶点变换
void VertexTransformForExtendObjectSelection(float fHitTestHeight, float fGlobal, mat4 worldMatrix, mat4 viewMatrix, mat4 projMatrix, mat4 worldviewprojMatrix)
{
	float fExtendHeight = fHitTestHeight;
	vec4 worldPos = worldMatrix * vec4(vertex.xyz, 1.0);
	vec4 height0Pos = worldPos;
	float bottomHeight = length(worldPos.xyz);
	// 将顶点变换到地表
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
	//底面顶点
	if(length(uv1.xyz) < 0.01)
	{
		vec4 clip_pos = projMatrix * viewMatrix * height0Pos;
		gl_Position = depthClampFarPlane(clip_pos);
	}
	else
	{
		// 高度在拾取范围内
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

// 对选择Pass的顶点变换
void VertexTransformForSelection(float fHitTestHeight, float fGlobal, mat4 worldMatrix, mat4 viewMatrix, mat4 projMatrix, mat4 inverseTransposeWorldMatrix)
{
	float fExtendHeight = fHitTestHeight;
	vec4 worldPos = worldMatrix * vec4(vertex.xyz, 1.0);
	// 将顶点变换到地表
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

