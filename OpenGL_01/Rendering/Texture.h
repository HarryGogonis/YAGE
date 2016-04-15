#pragma once
#include "GL/glew.h"

/**********************************************************************************************//**
 * @enum	TextureType
 *
 * @brief	Values that represent texture types.
 **************************************************************************************************/

enum TextureType
{
	Texture_Diffuse,
	Texture_Specular,
	Texture_Normal,
	Texture_Shadow
};

/**********************************************************************************************//**
 * @struct	Texture
 * \depricated
 * @brief	A texture. This struct is currently not used!
 **************************************************************************************************/
struct Texture
{
	GLuint id;
	std::string name;
	TextureType type;
};