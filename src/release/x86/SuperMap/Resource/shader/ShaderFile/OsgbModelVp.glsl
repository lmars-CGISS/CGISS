uniform float fCameraHeight;

uniform float hasEvevation;
uniform sampler2D elevationTexture;
uniform vec4 v4RectPos;
uniform vec4 v4HypsometricRectPos;
uniform float fExaggeration;
uniform float fBottom;
uniform float hasNormal;
uniform float hasLight;
uniform float hasAnalysisRegion;
uniform int bColorByHeight;

uniform vec4 ambient_light_colour;
uniform vec4 light_diffuse_colour;
uniform vec4 light_specular_colour;
uniform vec4 surface_ambient_colour;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;

varying vec4 clip_vertex;
#if SCISSOR_TEST
varying vec4 vPosition;
#endif

varying float wValue;
varying vec2 hypTexCoord;
varying float bHashHyp;

void DirectionalLight(in vec3 normal, inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	vec3 ecPosition = vec3(gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0));

	// 计算从表面点到摄像机的向量
	//vec3 eye = vec3(normalize(cameraPos-ecPosition));
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

vec4 CalculateHeight()
{
	vec2 vecRatio = vec2(v4RectPos.z - v4RectPos.x, v4RectPos.w - v4RectPos.y);
	vec2 texCoord = vec2(gl_Vertex.x - v4RectPos.x, gl_Vertex.y - v4RectPos.y);
	vec4 vecPos = gl_Vertex;
	vecPos.z = gl_Vertex.z * fExaggeration;
	
	texCoord.x = texCoord.x / vecRatio.x;
	texCoord.y = 1.0 - texCoord.y / vecRatio.y;
	
	if(texCoord.x > 1.0 || texCoord.x < 0.0 || texCoord.y > 1.0 || texCoord.y < 0.0)
	{
		return vecPos;
	}
	
	float height = texture2DLod(elevationTexture,texCoord.xy, 0.0).x;
	
	if(gl_Vertex.z >= height)
	{
		float fDepthOffset = clamp( (fCameraHeight - height - fBottom) * 0.0001 * (gl_Vertex.z + fBottom - height), 0.001, 3.0);
		vecPos.z = height + fDepthOffset;
		vecPos.w = vecPos.z;
	}
	
	return vecPos;
}

void main(void)
{
	vec4 vertexPos = gl_Vertex;
	vertexPos.z = vertexPos.z * fExaggeration;
	
	if(hasEvevation > 0.1)
	{
		vertexPos = CalculateHeight();
	}
	
	if(bColorByHeight == 1)
	{
		wValue = vertexPos.w + fBottom;
	}
	else
	{
		wValue = vertexPos.z + fBottom;
	}
	vertexPos.w = 1.0;
	
	bHashHyp = hasAnalysisRegion;
	if(hasAnalysisRegion > 0.1)
	{
		vec2 vecRatio = vec2(v4HypsometricRectPos.z - v4HypsometricRectPos.x, v4HypsometricRectPos.w - v4HypsometricRectPos.y);
		vec2 texCoord = vec2(vertexPos.x - v4HypsometricRectPos.x, vertexPos.y - v4HypsometricRectPos.y);
		texCoord.x = texCoord.x / vecRatio.x;
		texCoord.y = 1.0 - texCoord.y / vecRatio.y;
		hypTexCoord = clamp(texCoord, vec2(0.0), vec2(1.0));
	}
	
	if(hasNormal < 0.8 || hasLight < 0.8)
	{
		gl_FrontColor = gl_FrontMaterial.diffuse;
	}
	else
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
		mixColor.a = gl_FrontMaterial.diffuse.a;
		mixColor = clamp(mixColor, vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 1.0));
		gl_FrontColor = mixColor;
	}
	
	vec4 ambientColor = ambient_light_colour*surface_ambient_colour
		+ light_diffuse_colour*surface_diffuse_colour
		+ light_specular_colour*surface_specular_colour;
	ambientColor = clamp(ambientColor, vec4(0.0), vec4(1.0));
	gl_FrontColor = gl_FrontColor * ambientColor;
	
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
#if ADDTEX
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
#endif

	gl_Position = gl_ModelViewProjectionMatrix * vertexPos;
	gl_ClipVertex = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	clip_vertex = gl_ClipVertex;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
