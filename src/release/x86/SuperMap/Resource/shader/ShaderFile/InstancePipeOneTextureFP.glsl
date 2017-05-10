#if GL_ES
	precision mediump float;
#endif

#include <lib/ClipPlane.glsllib>

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

uniform sampler2D texture0;

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif
	vec4 color = gl_Color * texture2D(texture0, gl_TexCoord[0].xy);
	if (color.a < 0.1)
	{
		discard;
		return;
	}

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif
	gl_FragColor = color;
}