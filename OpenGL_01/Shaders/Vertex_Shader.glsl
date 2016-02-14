#version 430 core
layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_color;

out vec4 color;
uniform mat4 MVP;

void main(void)
{
	color = in_color;
	gl_Position = MVP * in_position;
}