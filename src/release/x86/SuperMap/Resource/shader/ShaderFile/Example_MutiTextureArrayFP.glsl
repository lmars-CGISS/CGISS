
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
	vec4 FColor, SColor;
if(index.x < 1.9)
	{
		FColor = texture2D(TextureArrayTex1, oUv[0].xy);
		SColor = texture2D(TextureArrayTex2, oUv[1].xy);		
	}
	else if(index.x < 3.9)
	{
		FColor = texture2D(TextureArrayTex3, oUv[2].xy);
		SColor = texture2D(TextureArrayTex4, oUv[3].xy);
	}
	else if(index.x < 5.9)
	{
		FColor = texture2D(TextureArrayTex5, oUv[4].xy);
		SColor = texture2D(TextureArrayTex6, oUv[5].xy);
	}
	else if(index.x < 7.9)
	{
		FColor = texture2D(TextureArrayTex7, oUv[6].xy);
		SColor = texture2D(TextureArrayTex8, oUv[7].xy);
	}
	
	gl_FragColor = FColor * SColor;
	gl_FragColor.rgb = gl_FragColor.rgb * gl_Color;
}

