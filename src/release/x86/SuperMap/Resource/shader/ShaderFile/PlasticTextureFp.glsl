uniform sampler2D texture0;

varying vec3 vNormal;
varying vec3 vViewVec;
varying vec4 vColor;

void main(void)
{
   float v = 0.5 * (1.0 + dot(normalize(vViewVec), vNormal));
   
   v = clamp(v, 0.2, 1.0);
   gl_FragColor.rgb = v * vColor.rgb;
   
   vec4 texColor = texture2D(texture0, gl_TexCoord[0].xy);
   
   gl_FragColor.rgb = gl_FragColor.rgb * texColor.rgb * gl_Color.rgb;
   
   gl_FragColor.a = gl_Color.a;
}