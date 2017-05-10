
varying float fHeight;

void main(void)
{
	vec4 oPos = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);

	gl_Position = oPos;
	gl_ClipVertex = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	fHeight = gl_Vertex.z;
}
