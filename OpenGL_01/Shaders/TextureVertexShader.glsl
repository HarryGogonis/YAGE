#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;

out vec2 texcoord;

uniform mat4 MVP;

void main(void)
{
	texcoord = in_texture;
	gl_Position = MVP * vec4(in_position,1);
}