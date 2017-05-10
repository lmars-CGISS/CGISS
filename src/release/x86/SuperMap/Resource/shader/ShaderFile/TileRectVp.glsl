
attribute vec4 vertex;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;
uniform mat4 texture0_matrix;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;

varying vec2 texCoord;
varying vec4 backColor;
varying float colorTolerance;

void main()
{
	backColor = surface_diffuse_colour;
	colorTolerance = surface_specular_colour.r;

	// 纹理坐标变换
	texCoord = vec2(texture0_matrix * uv0);

	// 顶点坐标变换
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
}

