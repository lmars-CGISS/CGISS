uniform int hasSelection;
uniform sampler2D selectionTexture;

uniform int hasEvevation;
uniform sampler2D elevationTexture;
uniform vec4 v4RectPos;

uniform float fCameraHeight;
uniform float fExaggeration;
uniform float fBottom;

uniform vec4 ambient_light_colour;
uniform vec4 light_diffuse_colour;
uniform vec4 light_specular_colour;
uniform vec4 surface_ambient_colour;
uniform vec4 surface_diffuse_colour;
uniform vec4 surface_specular_colour;

#if OPACITY
uniform float fOpacity;
#endif


varying vec4 vec4SelectionColor;  // 选中颜色
varying vec4 clip_vertex;
#if SCISSOR_TEST
varying vec4 vPosition;
#endif

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

	ambient += ambient_light_colour;
	diffuse += light_diffuse_colour * nDotVP;
	specular += light_specular_colour * powerFactor;
}

vec4 CalculateHeight()
{
	vec2 vecRatio = vec2(v4RectPos.z - v4RectPos.x, v4RectPos.w - v4RectPos.y);
	vec2 texCoord = vec2(gl_Vertex.x - v4RectPos.x, gl_Vertex.y - v4RectPos.y);
	vec4 vecPos = vec4(gl_Vertex.xyz, 1.0);
	
	texCoord.x = texCoord.x / vecRatio.x;
	texCoord.y = 1.0 - texCoord.y / vecRatio.y;
	
	if(texCoord.x > 1.0 || texCoord.x < 0.0 || texCoord.y > 1.0 || texCoord.y < 0.0)
	{
		return vecPos;
	}
	
	float height = texture2DLod(elevationTexture,texCoord.xy, 0.0).x;
	
	if(gl_Vertex.z < height)
	{
		vecPos.z = gl_Vertex.z;
	}
	else
	{
		float fDepthOffset = clamp( (fCameraHeight - height - fBottom) * 0.0001 * (gl_Vertex.z + fBottom - height), 0.001, 3.0);
		vecPos.z = height + fDepthOffset;
	}
	
	return vecPos;
}

void main(void)
{
	vec4 vertexPos = vec4(gl_Vertex.xyz, 1.0);
	vertexPos.z = vertexPos.z * fExaggeration;
	
	if(hasEvevation == 1)
	{
		vertexPos = CalculateHeight();
	}
	// 计算定向光各通道强度
	vec4 ambientTemp = vec4(0.0);
	vec4 diffuseTemp = vec4(0.0);
	vec4 specularTemp = vec4(0.0);

	vec3 newNormal = vec3(gl_NormalMatrix*gl_Normal);
	newNormal = normalize(newNormal);
		newNormal = newNormal * gl_NormalScale;
	
	DirectionalLight(newNormal, ambientTemp, diffuseTemp, specularTemp);
	vec4 mixColor = ambientTemp*surface_ambient_colour
		+ diffuseTemp*surface_diffuse_colour
		+ specularTemp*surface_specular_colour;
	mixColor.a = surface_diffuse_colour.a;
#if OPACITY
	mixColor.a = fOpacity;
#endif
	mixColor = clamp(mixColor, vec4(0.0, 0.0, 0.0, 0.0), vec4(1.0, 1.0, 1.0, 1.0));
	gl_FrontColor = mixColor;
	vec4SelectionColor = vec4(1.0, 1.0, 1.0, 1.0);

	if(hasSelection == 1 && vec4SelectionColor.a > 0.0 && gl_SecondaryColor.r < 0.99 && gl_SecondaryColor.g < 0.99 && gl_SecondaryColor.b < 0.99 && gl_SecondaryColor.a < 0.99)
	{
		vec4 selColor = texture2D(selectionTexture, vec2(0.5, 0.5));
		float r = abs(gl_SecondaryColor.r - selColor.r);
		float g = abs(gl_SecondaryColor.g - selColor.g);
		float b = abs(gl_SecondaryColor.b - selColor.b);
		float a = abs(gl_SecondaryColor.a - selColor.a);

		if(r < 0.003 && g < 0.003 && b < 0.003 && a < 0.003)
		{
			vec4SelectionColor = vec4(0.7,0.6,0.8,1.0);
		}
	}
	
	vec4SelectionColor = vec4SelectionColor * gl_Color;
	
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_Position = gl_ModelViewProjectionMatrix * vertexPos;
	gl_ClipVertex = gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0);
	clip_vertex = gl_ClipVertex;
#if SCISSOR_TEST
	vPosition = gl_Position;
#endif
}
