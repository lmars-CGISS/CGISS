uniform sampler2D elveTileTexture;
void main()
{	
	gl_FragColor = texture2D(elveTileTexture, gl_TexCoord[0].xy);
}