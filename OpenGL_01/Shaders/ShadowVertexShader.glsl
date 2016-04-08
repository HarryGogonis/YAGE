#version 430 core

uniform mat4 DepthMVP;
uniform mat4 Transform;

layout (location = 0) in vec3 position;

void main(void)
{
	gl_Position = DepthMVP * Transform * vec4(position, 1.0);
}