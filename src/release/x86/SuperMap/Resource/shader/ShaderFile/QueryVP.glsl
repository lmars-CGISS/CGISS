void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}


