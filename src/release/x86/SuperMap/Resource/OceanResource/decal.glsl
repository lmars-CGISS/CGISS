#ifdef OPENGL32
in vec4 position;
#else
attribute vec4 position;
#endif

uniform mat4 trit_mvProj;

vec4 overridePosition(in vec4 position);

void main()
{
    vec4 clipPos = trit_mvProj * position;
    gl_Position = overridePosition(clipPos);
}
