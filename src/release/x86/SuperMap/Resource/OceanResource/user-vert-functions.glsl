
float user_get_depth( in vec3 worldPos )
{
    return 1000.0;
}

/* You may use this hook to set any varying parameters you need for the user-functions.glsl fragment program.
   provided are the ocean vertex in world, eye, and projected coordinates. */
void user_intercept(in vec3 worldPosition, in vec3 localPosition, in vec4 eyePosition, in vec4 projectedPosition)
{

}

// Provides a point to override the final value of gl_Position.
// Useful for implementing logarithmic depth buffers etc.
vec4 overridePosition(in vec4 position)
{
    return position;
}
