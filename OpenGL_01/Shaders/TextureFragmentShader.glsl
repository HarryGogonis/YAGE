#version 430 core

in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;

void main(void)
{
	color = texture(myTextureSampler, UV).rgb;
}