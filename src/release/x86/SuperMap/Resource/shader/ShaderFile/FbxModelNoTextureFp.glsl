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

varying vec4 vec4SelectionColor;

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	if(vec4SelectionColor.a < 0.1 || gl_Color.a < 0.1)
	{
		discard;
	}
	
#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	gl_FragColor = gl_Color * vec4SelectionColor;
	
#if ALPHA_TEST
	AlphaTest(alphaTestType, gl_FragColor.a);
#endif
}
