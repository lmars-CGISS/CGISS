#if GL_ES
	precision mediump float;
#endif

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
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
	vec4 texColor = texture2D(texture0, texCoord.xy);
	texColor.a = 1.0;
	gl_FragColor = texColor* mixColor;
}
