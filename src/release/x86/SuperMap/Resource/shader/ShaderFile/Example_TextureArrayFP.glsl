
uniform sampler2D TextureArrayTex1;
uniform sampler2D TextureArrayTex2;
uniform sampler2D TextureArrayTex3;
uniform sampler2D TextureArrayTex4;
uniform sampler2D TextureArrayTex5;
uniform sampler2D TextureArrayTex6;
uniform sampler2D TextureArrayTex7;
uniform sampler2D TextureArrayTex8;

varying vec3 oUv[8];
varying vec2 index;

void main(void)
{
	if(index.x < 0.9)
	{
		gl_FragColor = texture2D(TextureArrayTex1, oUv[0].xy);
	}
	else if(index.x < 1.9)
	{
		gl_FragColor = texture2D(TextureArrayTex2, oUv[1].xy);
	}
	else if(index.x < 2.9)
	{
		gl_FragColor = texture2D(TextureArrayTex3, oUv[2].xy);
	}
	else if(index.x < 3.9)
	{
		gl_FragColor = texture2D(TextureArrayTex4, oUv[3].xy);
	}
	else if(index.x < 4.9)
	{
		gl_FragColor = texture2D(TextureArrayTex5, oUv[4].xy);
	}
	else if(index.x < 5.9)
	{
		gl_FragColor = texture2D(TextureArrayTex6, oUv[5].xy);
	}
	else if(index.x < 6.9)
	{
		gl_FragColor = texture2D(TextureArrayTex7, oUv[6].xy);
	}
	else if(index.x < 7.9)
	{
		gl_FragColor = texture2D(TextureArrayTex8, oUv[7].xy);
	}
	else
	{
		gl_FragColor = vec4(1,0,0,1);
	}
	
	gl_FragColor = gl_FragColor * gl_Color;
}
