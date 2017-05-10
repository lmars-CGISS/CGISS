#version 330 core
in mat2 rotationMat;

out vec4 color;

uniform sampler2D ourTexture;
void main()
{
	vec2 pt = gl_PointCoord -vec2(0.5);
    color = texture(ourTexture, rotationMat * pt + vec2(0.5));
}