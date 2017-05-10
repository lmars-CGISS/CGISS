attribute vec4 vertex;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;
uniform mat4 texture0_matrix;
uniform vec2 texture0_size;

uniform float fTexCoordScaleU;
uniform float fTexCoordScaleV;
uniform float fRasterTextureSize;

varying vec4 texCoord;

void main()
{
	// 计算纹理坐标
	vec4 scaleTexCoord = vec4(uv0.x * fTexCoordScaleU * fRasterTextureSize / texture0_size.x, 
		uv0.y * fTexCoordScaleV  * fRasterTextureSize / texture0_size.y, 0.0, 1.0);
	texCoord = texture0_matrix * scaleTexCoord;

	// 计算顶点坐标值
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
}
