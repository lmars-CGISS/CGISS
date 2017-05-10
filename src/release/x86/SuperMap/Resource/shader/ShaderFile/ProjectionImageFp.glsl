uniform sampler2D projectionImage;
uniform sampler2D depthTexture;
uniform int isFloatTex;
uniform vec3 v3AffineX;
uniform vec3 v3AffineY;

varying vec4 renderTextureCoord;
varying vec4 viewPos;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

void main()
{
	vec4 texCoord = renderTextureCoord / renderTextureCoord.w;
	texCoord.xy = texCoord.xy * 0.5 + 0.5;
	texCoord.y = 1.0 - texCoord.y;
	// 深度值	
	float depthValue = 1.0;
	vec4 depthColor = texture2D(depthTexture, texCoord.xy);
	depthValue = depthColor.x;
	if (isFloatTex != 1)
	{
		depthValue = unpackDepth(depthColor);
		depthValue = depthValue * 2.0 - 1.0;
	}
	// 深度偏差
	float bias = 5.0e-5;
	if (texCoord.x < 0.0 || texCoord.x > 1.0
		|| texCoord.y < 0.0 || texCoord.y > 1.0
		|| texCoord.z < 0.0 || texCoord.z > 1.0
		|| texCoord.z > (depthValue + bias))
	{
		discard;
		return;
	}

	vec2 finalTexCoord = texCoord.xy;
	finalTexCoord.y = 1.0 - finalTexCoord.y;
	
	texCoord.x = v3AffineX.x * finalTexCoord.x + v3AffineX.y * finalTexCoord.y + v3AffineX.z;
	texCoord.y = 1.0 - (v3AffineY.x * finalTexCoord.x + v3AffineY.y * finalTexCoord.y + v3AffineY.z);
	
	if(texCoord.x > 1.0 || texCoord.y > 1.0 || texCoord.x < 0.0 || texCoord.y < 0.0)
	{
		discard;
	}

	vec4 resultColor = texture2D(projectionImage, texCoord.xy);	
	gl_FragColor = resultColor;
}