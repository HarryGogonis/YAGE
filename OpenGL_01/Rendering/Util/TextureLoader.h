#pragma once
#include <SOIL.h>
#include <string>
#include <GL/glew.h>
#include <SOIL.h>

class TextureLoader
{
public:
	static GLuint LoadTexture(const std::string&);
};
