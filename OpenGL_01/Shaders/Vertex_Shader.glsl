#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out vec3 color;

uniform mat4 MVP;
uniform mat4 TransformMatrix;

void main(void)
{
	color = in_color;
	gl_Position = MVP * TransformMatrix * vec4(in_position, 1);
}