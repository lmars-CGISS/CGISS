#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 vertextColor;
layout (location = 2) in float angle_in;
layout (location = 3) in float size;

out mat2 rotationMat;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
	// 
	float angle = radians(angle_in);
	float sin_t = sin(angle);
	float cos_t = cos(angle);
	rotationMat = mat2(cos_t, -sin_t,
						sin_t, cos_t);
	// Point Size
	gl_PointSize = size;
	gl_Position = proj * view * model * vec4(position, 1.0);
}