
varying vec3 color;
varying float bDiscard;

void main()
{
	if(bDiscard > 0.01)
	{
		discard;
	}


	gl_FragColor.xyz = color;
	gl_FragColor.w = 1.0;
}
