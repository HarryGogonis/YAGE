#version 430 core

layout(location = 0) out vec4 out_color;

in vec3 color;

void main(void)
{
	out_color = vec4(color, 1);
}