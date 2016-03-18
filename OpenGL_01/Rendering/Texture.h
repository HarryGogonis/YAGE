#pragma once
#include "GL/glew.h"

enum TextureType
{
	Texture_Diffuse,
	Texture_Specular
};

struct Texture
{
	GLuint id;
	std::string name;
	TextureType type;
};