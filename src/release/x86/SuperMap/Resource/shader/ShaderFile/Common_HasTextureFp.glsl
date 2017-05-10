#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

// 传入纹理
uniform sampler2D texture0;

varying vec4 texCoord;
varying vec4 mixColor;

void main()
{
#if SCISSOR_TEST		
	if(!ScissorTest())
	{
		discard;
	}
#endif

#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	vec4 texColor = texture2D(texture0, texCoord.xy);
	if (texColor.a < 0.2)
	{
		discard;
	}
	gl_FragColor = texColor* mixColor;
}
