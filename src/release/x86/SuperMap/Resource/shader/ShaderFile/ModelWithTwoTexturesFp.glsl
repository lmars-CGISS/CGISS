#if GL_ES
precision mediump float;
#endif

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

// 传入纹理
uniform sampler2D texture0;
uniform sampler2D texture1;

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

	vec4 texColor = texture2D(texture0, texCoord.xy) * texture2D(texture1, texCoord.zw);
	if (texColor.a < 0.2)
	{
		discard;
	}
	gl_FragColor = texColor * mixColor;
}
