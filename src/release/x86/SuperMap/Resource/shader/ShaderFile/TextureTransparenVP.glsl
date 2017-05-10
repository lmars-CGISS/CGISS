varying vec3 transperantBackColor;
varying float transperantBackColorTolerance;
void main()
{
	transperantBackColor = gl_SecondaryColor.xyz;
	transperantBackColorTolerance = gl_SecondaryColor.w;

	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
	// ¶¥µã×ø±ê±ä»»
	gl_Position = ftransform();
}