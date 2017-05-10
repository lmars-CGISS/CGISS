void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	// ¶¥µã×ø±ê±ä»»
	gl_Position = ftransform();
}