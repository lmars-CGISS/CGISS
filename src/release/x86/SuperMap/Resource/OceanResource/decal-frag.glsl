uniform sampler2D trit_depthTexture;
uniform sampler2D trit_decalTexture;
uniform mat4 trit_inverseView;
uniform mat4 trit_decalMatrix;
uniform vec2 trit_inverseViewport;
uniform mat4 trit_projMatrix;
uniform vec4 trit_viewport;
uniform mat4 trit_inverseProjection;
uniform vec2 trit_depthRange;
uniform float trit_depthOffset;
uniform float trit_alpha;
uniform vec4 trit_lightColor;
uniform vec2 trit_colorUVOffset;
uniform vec3 trit_up;

void user_decal_color(in vec4 textureColor, in float alpha, in vec4 lightColor, inout vec4 finalColor);
void writeFragmentData(in vec4 finalColor, in vec4 Cdiffuse, in vec3 lightColor, in vec3 nNorm);

vec4 CalcEyeFromWindow(vec3 windowSpace)
{
    vec3 ndcPos;
    ndcPos.xy = ((2.0 * windowSpace.xy) - (2.0 * trit_viewport.xy)) / (trit_viewport.zw) - 1;
    ndcPos.z = (2.0 * windowSpace.z - trit_depthRange.x - trit_depthRange.y) / (trit_depthRange.y - trit_depthRange.x);

    vec4 clipPos;
    clipPos.w = trit_projMatrix[3][2] / (ndcPos.z - (trit_projMatrix[2][2] / trit_projMatrix[2][3]));
    clipPos.xyz = ndcPos * clipPos.w;

    vec4 eyePos = trit_inverseProjection * clipPos;

    return eyePos;
}

void main()
{
    vec2 depthUV = (gl_FragCoord.xy - trit_viewport.xy) * trit_inverseViewport;

#ifdef OPENGL32
    float depth = texture(trit_depthTexture, depthUV).x;
#else
    float depth = texture2D(trit_depthTexture, depthUV).x;
#endif

//gl_FragColor = vec4(depth, depth, depth, 1.0);
//return;

    gl_FragDepth = depth + trit_depthOffset;

    vec4 eyeSpace = CalcEyeFromWindow(vec3(gl_FragCoord.xy, depth));

    vec4 worldRelative = trit_inverseView * eyeSpace;

    vec4 clip = trit_decalMatrix * worldRelative;

    vec4 ndc = clip / clip.w;

    vec2 tc = (ndc.xy * 0.5) + 0.5;

    if (clamp(tc, 0, 1) != tc) {
        discard;
        return;
    }

    vec4 texcolor;
#ifdef OPENGL32
    texcolor.a = texture(trit_decalTexture, tc).a;
    texcolor.xyz = texture(trit_decalTexture, tc + trit_colorUVOffset).xyz;
#else
    texcolor.a = texture2D(trit_decalTexture, tc).a;
    texcolor.xyz = texture2D(trit_decalTexture, tc + trit_colorUVOffset).xyz;
#endif

    vec4 color = texcolor;
    color *= trit_lightColor;
    color.a *= trit_alpha;

    user_decal_color(texcolor, trit_alpha, trit_lightColor, color);

    writeFragmentData(color, color, trit_lightColor.xyz, trit_up);

}
