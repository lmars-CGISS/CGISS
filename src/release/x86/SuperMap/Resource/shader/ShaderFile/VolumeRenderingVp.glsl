attribute vec4 vertex;
attribute vec4 uv0;

uniform mat4 worldviewproj_matrix;
uniform mat4 worldview_matrix;
uniform mat4 texture0_matrix;

varying vec4 viewPos;
varying vec4 texCoord;

void main()
{
	viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	texCoord = texture0_matrix * uv0;

	// ¶¥µã×ø±ê±ä»»
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
}
