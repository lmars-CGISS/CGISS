varying vec3 vNormal;
varying vec3 vViewVec;
varying vec4 vColor;

void DirectionalLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	vec3 ecPosition = vec3(gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0));

	// ����ӱ���㵽�����������
	vec3 eye = -normalize(ecPosition);
	vec3 vp = normalize(vec3(gl_LightSource[0].position));
	// ������������ߵİ�����
	vec3 halfVector = normalize(vp+eye);
	
	float nDotVP = max(0.0, dot(normal, vp));
	float nDotHV = dot(normal, halfVector);

	// �ֲڶȣ�ԽСԽ�⻬
	float shininess = 1.0;//gl_FrontMaterial.shininess;
	// ���淴���ǿ������
	float powerFactor = max(0.0, pow(nDotHV, shininess));

	ambient += gl_LightSource[0].ambient;
	diffuse += gl_LightSource[0].diffuse * nDotVP;
	specular += gl_LightSource[0].specular * powerFactor;
}

void main(void)
{
   gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);

   // ������������
	 gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
   // World-space lighting
//   vNormal = gl_Normal;
//   vViewVec = gl_Position.xyz - gl_Vertex.xyz;
   
   vNormal = gl_NormalMatrix * gl_Normal;
   vViewVec = vec3(gl_LightSource[0].position);
   vColor = gl_FrontMaterial.diffuse;   
   
   // ���㶨����ͨ��ǿ��
	 vec4 ambientTemp = vec4(0.0);
	 vec4 diffuseTemp = vec4(0.0);
	 vec4 specularTemp = vec4(0.0);

	 vec3 newNormal = vec3(vNormal);
	 newNormal = normalize(newNormal);
        newNormal = newNormal * gl_NormalScale;
	
	 DirectionalLight(newNormal, ambientTemp, diffuseTemp, specularTemp);
	 vec4 mixColor = gl_FrontLightModelProduct.sceneColor
		+ ambientTemp*gl_FrontMaterial.ambient
		+ diffuseTemp*gl_FrontMaterial.diffuse
		+ specularTemp*gl_FrontMaterial.specular;
	
	 gl_FrontColor = mixColor;
}