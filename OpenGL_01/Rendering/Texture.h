#pragma once
#include "GL/glew.h"

enum TextureType
{
	Texture_Diffuse,
	Texture_Specular,
	Texture_Normal
};

struct Texture
{
	GLuint id;
	std::string name;
	TextureType type;
};