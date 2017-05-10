
varying float fTranslate[4];
varying float fScale[2];
varying float fMaxMipLev[2];
varying vec4 vecTileWidth;
varying float fWIndex;

#if SCISSOR_TEST
varying vec4 vPosition;
#endif

uniform mat4 worldviewproj_matrix;
uniform mat4 texture0_matrix;
uniform mat4 texture1_matrix;
uniform vec4 texture0_size;
uniform vec4 texture1_size;
uniform vec4 texture2_size;
uniform vec4 texture3_size;
uniform vec4 texture4_size;
uniform vec4 texture5_size;
uniform vec4 texture6_size;
uniform vec4 texture7_size;

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
	float shininess = 50.0;//gl_FrontMaterial.shininess;
	// 镜面反射光强度因子
	float powerFactor = max(0.0, pow(nDotHV, shininess));

	ambient += gl_LightSource[0].ambient;
	diffuse += gl_LightSource[0].diffuse * nDotVP;
	specular += gl_LightSource[0].specular * powerFactor;
}

void CalculateMatrix(in int nZ, inout float XTran, inout float YTran, inout float scale)
{
	int nPow8  = int(pow(2.0, 8.0));
	
	int nDel8 = nZ / nPow8;
	int nDel16 = nDel8 / nPow8;
	
	YTran = float(nZ - nDel8 * nPow8);
	XTran = float(nDel8 - nDel16 * nPow8);
	int nLevel = nDel16;
	
	scale = 1.0 / pow(2.0, float(nLevel));
}

void main(void)
{
	// 计算定向光各通道强度
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);

	vec3 newNormal = vec3(gl_NormalMatrix*gl_Normal);
	newNormal = normalize(newNormal);
        newNormal = newNormal * gl_NormalScale;
	
	DirectionalLight(newNormal, ambientTemp, diffuseTemp, specularTemp);
	vec4 mixColor = gl_FrontLightModelProduct.sceneColor
		+ ambientTemp*gl_FrontMaterial.ambient
		+ diffuseTemp*gl_FrontMaterial.diffuse
		+ specularTemp*gl_FrontMaterial.specular;
	
	mixColor = clamp(mixColor, vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 1.0));
	gl_FrontColor = mixColor;
	
	gl_Position = worldviewproj_matrix * vec4(gl_Vertex.xyz, 1.0);
	gl_ClipVertex = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif

	gl_TexCoord[0].xyz = vec3(texture0_matrix * gl_MultiTexCoord0);
	gl_TexCoord[1].xyz = vec3(texture1_matrix * gl_MultiTexCoord1);
	
	int nZ = int(gl_TexCoord[0].z);	
	CalculateMatrix(nZ, fTranslate[0], fTranslate[1], fScale[0]);	
	
	nZ = int(gl_TexCoord[1].z);
	CalculateMatrix(nZ, fTranslate[2], fTranslate[3], fScale[1]);
	
	fWIndex = gl_MultiTexCoord0.w;

	if(fWIndex < 3.6)
	{
		if(fWIndex < 1.6)
		{
			vecTileWidth.xy = vec2(fScale[0] * texture0_size.x, fScale[0] * texture0_size.y);
			vecTileWidth.zw = vec2(fScale[1] * texture1_size.x, fScale[1] * texture1_size.y);
		}
		else
		{
			vecTileWidth.xy = vec2(fScale[0] * texture2_size.x, fScale[0] * texture2_size.y);
			vecTileWidth.zw = vec2(fScale[1] * texture3_size.x, fScale[1] * texture3_size.y);
		}
	}
	else
	{
		if(fWIndex < 5.6)
		{
			vecTileWidth.xy = vec2(fScale[0] * texture4_size.x, fScale[0] * texture4_size.y);
			vecTileWidth.zw = vec2(fScale[1] * texture5_size.x, fScale[1] * texture5_size.y);
		}
		else
		{
			vecTileWidth.xy = vec2(fScale[0] * texture6_size.x, fScale[0] * texture6_size.y);
			vecTileWidth.zw = vec2(fScale[1] * texture7_size.x, fScale[1] * texture7_size.y);
		}
	}
	
//	fTileWidth[0] = fScale[0] * texture0_size.x;
	fMaxMipLev[0] = log2(max(vecTileWidth.x, vecTileWidth.y));
	
//	fTileWidth[1] = fScale[1] * texture1_size.x;
	fMaxMipLev[1] = log2(max(vecTileWidth.z, vecTileWidth.w));
	
}


