# version 440 core

// Values interpolated via the vertex shader
in vec2 UV;
in vec4 particleColor;

out vec4 color;

uniform sampler2D particle_texture;

void main()
{
	color = texture(particle_texture, UV) * particleColor;
	//color = vec4(1.0f);
}