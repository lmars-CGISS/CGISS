
uniform mat4 view_matrix;
uniform vec4 surface_ambient_colour;

uniform mat4 texture0_matrix;
uniform vec4 texture0_size;

varying float fTranslate[2];
varying float fScale;
varying float fMaxMipLev;
varying vec2 vecTileWidth;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

void CalculateMatrix(in int nZ, inout float XTran, inout float YTran, inout float scale)
{
	int nPow8  = int(pow(2.0, 8.0));
	
	int nDel8 = nZ / nPow8;
	int nDel16 = nDel8 / nPow8;
	
	YTran = float(nZ - nDel8 * nPow8);
	XTran = float(nDel8 - nDel16 * nPow8);
	int nLevel = nDel16;
	
	scale = 1.0 / pow(2.0, float(nLevel));
}

void main(void)
{
	// 构建视觉坐标系下的变换矩阵
	vec4 viewPos = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	vec4 origViewPos = view_matrix * vec4(0.0, 0.0, 0.0, 1.0);
	vec4 fixedAxis = viewPos - origViewPos;
	vec3 yAxis = normalize(fixedAxis.xyz);
	vec4 cameraViewPos = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 cameraViewVector = cameraViewPos - viewPos;
	vec3 zAxis = normalize(cameraViewVector.xyz);
	vec3 xAxis = normalize(cross(yAxis, zAxis));
	zAxis = cross(xAxis, yAxis);
	mat3 matrix = mat3(xAxis, yAxis, zAxis);
	
	// 计算顶点坐标值
	vec3 offset = gl_Normal.xzy;
	offset = matrix * offset;
	viewPos.xyz += offset.xyz;
	gl_Position = gl_ProjectionMatrix * viewPos;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
	gl_ClipVertex = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	
	gl_FrontColor = surface_ambient_colour;

	vec3 oUV;
	oUV = vec3(texture0_matrix * gl_MultiTexCoord0);
	gl_TexCoord[0].xy = oUV.xy;
	
	int nZ = int(gl_MultiTexCoord0.w);
	
	CalculateMatrix(nZ, fTranslate[0], fTranslate[1], fScale);
	
	vecTileWidth = vec2(fScale * texture0_size.x, fScale * texture0_size.y);
	fMaxMipLev = log2(max(vecTileWidth.x, vecTileWidth.y));
}


