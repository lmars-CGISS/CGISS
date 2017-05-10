#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

#if ALPHA_TEST
#include <lib/AlphaTest.glsllib>
uniform float alphaTestType;
#endif

uniform sampler2D diffuseTexture;

varying vec4 vec4SelectionColor;

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	vec4 color = texture2D(diffuseTexture, gl_TexCoord[0].xy);
	
	if(vec4SelectionColor.a < 0.1)
	{
		discard;
	}

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif
	
	gl_FragColor = color * vec4SelectionColor;
	gl_FragColor= gl_FragColor * gl_Color;

	if(gl_FragColor.a < 0.1)
	{
		discard;
	}
	
#if ALPHA_TEST
	AlphaTest(alphaTestType, gl_FragColor.a);
#endif
}
