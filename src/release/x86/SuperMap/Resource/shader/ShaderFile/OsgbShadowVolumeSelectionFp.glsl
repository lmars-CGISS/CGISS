#include <lib/ClipPlane.glsllib>

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

varying vec4 vecVertexColor;
varying float fWindowZ;

void writeDepthClampedToFarPlane()
{
    gl_FragDepth = min(fWindowZ * gl_FragCoord.w, 1.0);
}

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
	writeDepthClampedToFarPlane();
}
