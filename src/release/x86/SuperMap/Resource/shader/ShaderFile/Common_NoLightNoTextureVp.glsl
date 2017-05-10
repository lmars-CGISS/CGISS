attribute vec4 vertex;

uniform mat4 worldviewproj_matrix;
uniform vec4 surface_diffuse_colour;

varying vec4 mixColor;

varying vec4 clip_pos;
varying float fWindowZ;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

#if CLIP
varying vec4 clip_vertex;
#endif

// 将投影后坐标移到视景体内
vec4 depthClampFarPlane(vec4 clipPos)
{
    fWindowZ = (0.5 * (clipPos.z / clipPos.w) + 0.5) * clipPos.w;
    clipPos.z = min(clipPos.z, clipPos.w);
    return clipPos;
}

void main()
{
	// 顶点坐标变换
	vec4 vVertex = vertex;
	vVertex.w = 1.0;
	clip_pos = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
	gl_Position = depthClampFarPlane(clip_pos);
	
	mixColor = surface_diffuse_colour;

#if CLIP
	clip_vertex = gl_ModelViewMatrix * vVertex;
#endif

#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
