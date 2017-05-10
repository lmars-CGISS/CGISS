
uniform mat4 vertexToTexcoordMatrix;
varying vec4 texCoord;
void main()
{
	vec4 viewPos = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	texCoord = vertexToTexcoordMatrix * viewPos;
		
	gl_Position = ftransform();
}