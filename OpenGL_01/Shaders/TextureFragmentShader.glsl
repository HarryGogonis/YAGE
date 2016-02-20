#version 430 core
layout(location = 0) out vec4 out_color;

uniform sampler2D texture1;

in vec2 texcoord;

void main(void)
{
	vec4 color = texture(texture1, texcoord).rgba;
	out_color = color;
}