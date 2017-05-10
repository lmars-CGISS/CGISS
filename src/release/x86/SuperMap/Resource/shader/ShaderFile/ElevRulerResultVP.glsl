uniform sampler2D RulerTexture;
uniform float L1;
uniform float L2;
varying float dTotalArea;

void main()
{
	float texCoordInv = 0.0009765625;//1.0 / 1024.0;

	for (int i = 0; i < 1023; ++i)
	{
		vec2 texCoord0 = vec2(gl_MultiTexCoord0.x, i * texCoordInv);
		vec2 texCoord1 = vec2(gl_MultiTexCoord0.x, i * texCoordInv + texCoordInv);
		vec2 texCoord2 = vec2(gl_MultiTexCoord0.x + texCoordInv, i * texCoordInv + texCoordInv);
		vec2 texCoord3 = vec2(gl_MultiTexCoord0.x + texCoordInv, i * texCoordInv);

		float h0, h1, h2, h3;
		h0 = texture2DLod(RulerTexture, texCoord0, 0.0).x;
		h1 = texture2DLod(RulerTexture, texCoord1, 0.0).x;
		h2 = texture2DLod(RulerTexture, texCoord2, 0.0).x;
		h3 = texture2DLod(RulerTexture, texCoord3, 0.0).x;

	    if (h0 < 15000.0 && h2 < 15000.0 && h3 < 15000.0)
	    {
			float hDelt0 = h3 - h0;
			float hDelt1 = h2 - h0;
			dTotalArea += 0.5 * sqrt(L1*L1 * ((hDelt0 - hDelt1)*(hDelt0 - hDelt1) + L2*L2) + L2*L2*hDelt1*hDelt1);
		}

		if (h0 < 15000.0 && h1 < 15000.0 && h2 < 15000.0)
		{
			float hDelt0 = h1 - h0;
			float hDelt1 = h2 - h0;
			dTotalArea += 0.5 * sqrt(L2*L2 * ((hDelt0 - hDelt1)*(hDelt0 - hDelt1) + L1*L1) + L1*L1*hDelt0*hDelt0);
		}
	}	

	// ¶¥µã×ø±ê±ä»»
	gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);
}
