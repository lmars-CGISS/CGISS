
uniform mat4 texWorldViewProjMatrix0;
uniform mat4 texWorldViewProjMatrix1;
uniform mat4 texWorldViewProjMatrix2;

varying vec4 shadowmapTexCoord0;
varying vec4 shadowmapTexCoord1;
varying vec4 shadowmapTexCoord2;
varying float cameraDepth;

void main()
{
	// ����ƹ�ռ��µĶ���λ��
	shadowmapTexCoord0 = texWorldViewProjMatrix0 * vec4(gl_Vertex.xyz, 1.0);
	shadowmapTexCoord1 = texWorldViewProjMatrix1 * vec4(gl_Vertex.xyz, 1.0);
	shadowmapTexCoord2 = texWorldViewProjMatrix2 * vec4(gl_Vertex.xyz, 1.0);

	// ͶӰ����Ļ�ϵ�λ��
	gl_Position = ftransform();
	// ����������
	cameraDepth = gl_Position.z;
	
	gl_ClipVertex = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
}
