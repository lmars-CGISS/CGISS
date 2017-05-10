attribute vec4 vertex;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;

varying vec4 texCoord;
varying vec4 clip_pos;
varying float fWindowZ;

// 将投影后坐标移到视景体内
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

void main()
{
	texCoord = uv0;
	clip_pos = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
	gl_Position = depthClampFarPlane(clip_pos);
}

