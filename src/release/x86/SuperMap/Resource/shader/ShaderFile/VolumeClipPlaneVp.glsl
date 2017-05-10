attribute vec4 vertex;

uniform mat4 worldviewproj_matrix;
uniform mat4 worldview_matrix;
uniform mat4 viewToTextureMatrix;

varying vec4 texCoord;

void main()
{
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	texCoord = viewToTextureMatrix * viewPos;

	// ¶¥µã×ø±ê±ä»»
	gl_Position = worldviewproj_matrix * vec4(vertex.xyz, 1.0);
}
