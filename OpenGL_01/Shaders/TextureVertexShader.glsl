#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;

out vec2 UV;

uniform mat4 MVP;

void main(void)
{
	gl_Position = MVP * vec4(in_position,1);
	UV = in_uv;
}