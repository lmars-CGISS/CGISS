varying vec3 vNormal;
varying vec3 vViewVec;
varying vec4 vColor;

void main(void)
{
   float v = 0.5 * (1.0 + dot(normalize(vViewVec), vNormal));
   
   v = clamp(v, 0.2, 1.0);
   
   gl_FragColor.rgb = v * vColor.rgb  * gl_Color.rgb;
   
   gl_FragColor.a = gl_Color.a;
}