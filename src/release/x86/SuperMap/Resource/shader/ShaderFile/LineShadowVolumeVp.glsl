// uv0.x存储选中状态，0.0为非选中,1.0为选中
// uv1.xyz存储了顶点的纵向拉伸量，包括大小和方向
// uv2.xyz存储了顶点的横向拉伸方向
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

const float fTempScreen = 1236.077;

// 将投影后坐标移到视景体内
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

// 计算线宽度
float ComputeLineWidth()
{
	vec4 worldPos = world_matrix * vec4(vertex.xyz, 1.0);
	return lineWidth * length(camera_position - worldPos.xyz) / fTempScreen;
}

void main()
{
#if SELECTION
	float shadowVolumeWidth = ComputeLineWidth();
	// 选择时加宽一些，方便选中
	shadowVolumeWidth = shadowVolumeWidth * 3.0;

	vec4 worldPos = world_matrix * vec4(vertex.xyz, 1.0);
	// 将顶点变换到地表
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

