
uniform sampler2D texture0;
uniform int isFloatTex;
uniform vec3 visibleColor;
uniform vec3 hiddenColor;
uniform vec4 surface_diffuse_colour;

varying vec4 renderTextureCoord;
varying float texCoordX;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

void main()
{
	vec4 resultColor = vec4(visibleColor, 1.0);
	vec4 texCoord = renderTextureCoord / renderTextureCoord.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	texCoord.y = 1.0 - texCoord.y;

	if (abs(texCoordX - 1.0) < 0.00001)
	{
		// 获取纹理中存储的深度值
		vec4 depthColor = texture2D(texture0, texCoord.xy);
		float depth = depthColor.x;
		if (isFloatTex != 1)
		{
			depth = unpackDepth(depthColor);
			depth = depth * 2.0 - 1.0;
		}
		
		if (depth < 1.0 && depth < texCoord.z)
		{
			resultColor = vec4(hiddenColor, 1.0);
		}
	}
	else
	{
		resultColor = vec4(0.4,0.4,0.4,1.0);
	}
	gl_FragColor = resultColor * surface_diffuse_colour;
}
