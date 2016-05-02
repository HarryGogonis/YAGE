#include "TextureLoader.h"
#include <cassert>
#include <iostream>

int file_exist(const char *filename)
{
	struct stat   buffer;
	return (stat(filename, &buffer) == 0);
}

GLuint TextureLoader::LoadTexture(const std::string& texturePath)
{
	assert(!texturePath.empty());
	if (!file_exist(texturePath.c_str()))
	{
		std::cout << "ERROR: cannot find file " << texturePath << std::endl;
		return 0;
	}
	GLuint texture = SOIL_load_OGL_texture(
		texturePath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	if (!texture)
		std::cout << "ERROR loading texture  " << texturePath << " " << SOIL_last_result() << std::endl;
	return texture;
}
