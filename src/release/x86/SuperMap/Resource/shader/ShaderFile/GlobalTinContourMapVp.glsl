
attribute vec4 vertex;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;
uniform mat4 texture0_matrix;

uniform vec4 ambient_light_colour;
uniform vec4 light_diffuse_colour;
uniform vec4 light_specular_colour;
uniform vec4 surface_ambient_colour;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;

varying vec4 texCoord;
varying vec4 oriTexCoord;
varying vec4 mixColor;
varying float height;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

#if CLIP
varying vec4 clip_vertex;
#endif

void main()
{
	mixColor = ambient_light_colour*surface_ambient_colour
		+ light_diffuse_colour*surface_diffuse_colour
		+ light_specular_colour*surface_specular_colour;

	// 纹理坐标变换
	texCoord.xy = vec2(texture0_matrix * uv0);
	oriTexCoord = uv0;

	height = vertex.w;

	// 顶点坐标变换
	vec4 vVertex = vertex;
	vVertex.w = 1.0;
	gl_Position = worldviewproj_matrix * vVertex;

#if CLIP
	clip_vertex = gl_ModelViewMatrix * vertex;
#endif

#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
