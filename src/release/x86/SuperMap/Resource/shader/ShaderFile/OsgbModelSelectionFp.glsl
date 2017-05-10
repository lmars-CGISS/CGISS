#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

varying vec4 vecVertexColor;

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	if(vecVertexColor.a < 0.001)
	{
		discard;
	}

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif
	
	gl_FragColor = vecVertexColor;
}
