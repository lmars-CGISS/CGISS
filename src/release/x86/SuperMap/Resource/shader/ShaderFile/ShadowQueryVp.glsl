attribute vec4 vertex;
attribute vec3 normal;

uniform mat4 worldview_matrix;
uniform mat4 projection_matrix;
uniform mat4 renderTextureMatrix0;
uniform mat4 renderTextureMatrix1;
uniform mat4 renderTextureMatrix2;

varying vec4 shadowmapTexCoord0;
varying vec4 shadowmapTexCoord1;
varying vec4 shadowmapTexCoord2;
varying vec4 windowPos;
varying float cameraDepth;

void main()
{
	// ����ƹ�ռ��µĶ���λ��
	vec4 texCoord = renderTextureMatrix0 * vec4(vertex.xyz, 1.0);
	shadowmapTexCoord0 = texCoord / texCoord.w;
	shadowmapTexCoord0.xy = shadowmapTexCoord0.xy * 0.5 + 0.5;
	shadowmapTexCoord0.y = 1.0 - shadowmapTexCoord0.y;
	
	texCoord = renderTextureMatrix1 * vec4(vertex.xyz, 1.0);
	shadowmapTexCoord1 = texCoord / texCoord.w;
	shadowmapTexCoord1.xy = shadowmapTexCoord1.xy * 0.5 + 0.5;
	shadowmapTexCoord1.y = 1.0 - shadowmapTexCoord1.y;
	
	texCoord = renderTextureMatrix2 * vec4(vertex.xyz, 1.0);
	shadowmapTexCoord2 = texCoord / texCoord.w;
	shadowmapTexCoord2.xy = shadowmapTexCoord2.xy * 0.5 + 0.5;
	shadowmapTexCoord2.y = 1.0 - shadowmapTexCoord2.y;

	// �������Ӿ�����ϵ�е�����ֵ
	vec4 viewPos = worldview_matrix * vec4(vertex.xyz, 1.0);
	// ������Ļ����
	windowPos = projection_matrix * viewPos;
	cameraDepth = windowPos.z;
	
	// ����ƫ�ƺ��λ��
	viewPos.xyz += normal;
	gl_Position = projection_matrix * viewPos;
}
