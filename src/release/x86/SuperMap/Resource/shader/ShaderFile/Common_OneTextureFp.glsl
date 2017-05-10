#if GL_ES
	precision mediump float;
#endif

#if CLIP
#include <lib/ClipPlane.glsllib>
#endif

uniform sampler2D texture0;
uniform vec4 surface_diffuse_colour;

#if ALPHA_REJECT
uniform float alphaReject;
#endif

#if MIXCOLOR
varying vec4 mixColor;
#endif

varying vec4 texCoord;

void main()
{
#if CLIP
	#include <lib/ClipPlaneMainCode.glsllib>
#endif

	vec4 color = surface_diffuse_colour * texture2D(texture0, texCoord.xy);
#if MIXCOLOR
	color = color * mixColor;
#endif
	gl_FragColor = color;
	
	float fReject = 0.2;
#if ALPHA_REJECT
	fReject = alphaReject;
#endif

	if(gl_FragColor.a < fReject)
	{
		discard;
	}
}