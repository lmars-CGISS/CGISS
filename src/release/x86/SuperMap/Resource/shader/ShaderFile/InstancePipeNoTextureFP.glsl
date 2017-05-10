#include <lib/ClipPlane.glsllib>

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())	
	{
		discard;
	}
#endif

	if (gl_Color.a < 0.1)
	{
		discard;
		return;
	}

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif
	gl_FragColor = gl_Color;
}