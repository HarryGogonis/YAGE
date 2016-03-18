#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec3 in_normal;

out vec2 UV;
out vec3 Normal;
out vec4 Position;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 TranslationMatrix;
uniform mat3 NormalMatrix;

void main(void)
{
	UV = in_texture;
	Normal = normalize(NormalMatrix * in_normal);
	vec4 mod_position = TranslationMatrix * vec4(in_position, 1);
	Position = MV * mod_position;
	gl_Position = MVP * mod_position;
}