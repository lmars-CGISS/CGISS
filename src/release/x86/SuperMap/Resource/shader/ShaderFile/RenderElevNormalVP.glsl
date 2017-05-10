varying vec2 Translation;

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;

	if (gl_TexCoord[0].z > 2.5)
	{
		Translation.x = 0.5;
		Translation.y = 0.0;
	}
	else if (gl_TexCoord[0].z > 1.5)
	{
		Translation.x = 0.0;
		Translation.y = 0.0;
	}
	else if (gl_TexCoord[0].z > 0.5)
	{
		Translation.x = 0.5;
		Translation.y = 0.5;
	}
	else
	{
		Translation.x = 0.0;
		Translation.y = 0.5;
	}

	// ¶¥µã×ø±ê±ä»»
	gl_Position = ftransform();
}