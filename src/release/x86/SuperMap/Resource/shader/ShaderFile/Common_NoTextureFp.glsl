#if GL_ES
	precision mediump float;
#endif

#if SCISSOR_TEST
#include <lib/ScissorTest.glsllib>
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

#if ADDTEX
// ´«ÈëÎÆÀí
uniform sampler3D texture0;
varying vec4 texCoord;
#endif

varying vec4 mixColor;
varying float fWindowZ;

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

#if ADDTEX
	vec4 volumeColor = texture3D(texture0, texCoord.xyz);

	if(texCoord.x < 0.0 || texCoord.x > 1.0 || texCoord.y < 0.0 || texCoord.y > 1.0 || texCoord.z < 0.0 || texCoord.z > 1.0)
	{
		volumeColor.rgb = vec3(1.0,1.0,1.0);
	}
	if(volumeColor.r < 0.01 && volumeColor.g < 0.01 && volumeColor.b < 0.01 )
	{
		volumeColor.rgb = vec3(1.0,1.0,1.0);
	}
	mixColor.rgb = mixColor.rgb * volumeColor.rgb;
#endif

	gl_FragColor = mixColor;
}