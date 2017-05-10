varying vec3 vNormal;
varying vec3 vViewVec;
varying vec4 vColor;

void DirectionalLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	vec3 ecPosition = vec3(gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0));

	// 计算从表面点到摄像机的向量
	vec3 eye = -normalize(ecPosition);
	vec3 vp = normalize(vec3(gl_LightSource[0].position));
	// 计算视线与光线的半向量
	vec3 halfVector = normalize(vp+eye);
	
	float nDotVP = max(0.0, dot(normal, vp));
	float nDotHV = dot(normal, halfVector);

	// 粗糙度，越小越光滑
	float shininess = 1.0;//gl_FrontMaterial.shininess;
	// 镜面反射光强度因子
	float powerFactor = max(0.0, pow(nDotHV, shininess));

	ambient += gl_LightSource[0].ambient;
	diffuse += gl_LightSource[0].diffuse * nDotVP;
	specular += gl_LightSource[0].specular * powerFactor;
}

void main(void)
{
   gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);

   // 计算纹理坐标
	 gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
   // World-space lighting
//   vNormal = gl_Normal;
//   vViewVec = gl_Position.xyz - gl_Vertex.xyz;
   
   vNormal = gl_NormalMatrix * gl_Normal;
   vViewVec = vec3(gl_LightSource[0].position);
   vColor = gl_FrontMaterial.diffuse;   
   
   // 计算定向光各通道强度
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