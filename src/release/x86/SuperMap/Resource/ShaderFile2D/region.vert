#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 vertextColor;

flat out vec4 regionColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	regionColor = vertextColor;
	gl_Position = proj * view * model * vec4(position, 1.0);
}