void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	// ��������任
	gl_Position = ftransform();
}