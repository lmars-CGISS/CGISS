uniform mat4 renderSkylineMatrix;
uniform sampler2D SkylineTexture;
uniform int texHeight;
uniform int isFloatTex;

float unpackDepth(const in vec4 rgba_depth)
{
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0));
	float depth=dot(rgba_depth, bitShifts);
	return depth;
}

void main()
{
	vec4 texToVertexCoord = vec4(0.0,0.0,0.0,1.0);
	
	if (gl_MultiTexCoord0.x >= 0)
	{
		float inv_texHeight = 1.0 / float(texHeight);
		for (int i = 0; i < texHeight; ++i)
		{
			vec2 texCoord = vec2(gl_MultiTexCoord0.x, i * inv_texHeight);
			vec4 depthColor = texture2DLod(SkylineTexture, texCoord,0.0);
			float depth= depthColor.x;
			if (isFloatTex != 1)
			{
				depth = unpackDepth(depthColor);
				depth = depth * 2.0 - 1.0;
			}
			if (depth < 1.0)
			{
				texCoord.y = 1.0 - texCoord.y;
				texCoord = texCoord * 2.0 - 1.0;
				texToVertexCoord = vec4(texCoord, depth, 1.0);
				break;
			}
		}	
		gl_Position = renderSkylineMatrix * texToVertexCoord;
	}
	else
	{
		gl_Position = gl_ModelViewProjectionMatrix * texToVertexCoord;
	}
}