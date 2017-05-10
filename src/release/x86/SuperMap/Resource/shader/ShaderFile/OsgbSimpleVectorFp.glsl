#if GL_ES
	precision mediump float;
#endif

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if STENCIL_SELECTED
varying float fSelected;
#endif

varying vec4 mixColor;

void main()
{
	if(mixColor.a < 0.01)
	{
		discard;
	}
#if STENCIL_SELECTED
	if(fSelected < 0.5)
	{
		discard;
	}
#endif

#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	gl_FragColor = mixColor;
}