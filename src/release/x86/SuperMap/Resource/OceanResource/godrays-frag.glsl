#ifdef OPENGL32
in vec3 intensity;
in vec3 view;
out vec4 fragColor;
#else
varying vec3 intensity;
varying vec3 view;
#endif

uniform vec3 sunDir;
uniform vec3 sunColor;
uniform mat3 invBasis;
uniform float visibility;

float ComputeMieScattering(in vec3 V, in vec3 sunDir)
{
    const float g = 0.924;
//    const float g = 0.7;

    float cosTheta = dot(normalize(V), normalize(sunDir));

    float num = 1.0 - g * g;
    float den = (1.0 + g * g - 2.0 * g * cosTheta);

    den = sqrt(den);
    den = den * den * den;

    float phase = (1.0 / (4.0 * 3.14159)) * (num / den);

    return phase;
}

void main()
{
    vec3 up = invBasis * vec3(0,0,1);
    vec3 refractedLight = refract(-sunDir, up, 1.0/1.333);

    float phase = ComputeMieScattering(-normalize(view), refractedLight);

    vec3 finalIntensity = intensity * vec3(phase, phase, phase);
    finalIntensity *= exp(-length(view) * (3.912 / visibility) * 8.0);

    finalIntensity *= sunColor;

    vec4 color = vec4(finalIntensity, 1.0);

    color = clamp(color, 0.0, 1.0);

#ifdef OPENGL32
    fragColor = color;
#else
    gl_FragColor = color;
#endif
}
