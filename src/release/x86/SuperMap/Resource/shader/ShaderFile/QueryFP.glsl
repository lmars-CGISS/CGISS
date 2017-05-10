uniform sampler3D VolTexture;


void main()
{
	float fValue = texture3D(VolTexture, gl_TexCoord[0].xyz).x;
	gl_FragColor = vec4(fValue, fValue, fValue, 1.0);
}
