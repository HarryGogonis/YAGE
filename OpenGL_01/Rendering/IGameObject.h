#pragma once
#include <vector>
#include "GL\glew.h"
#include "GL\freeglut.h"

#include "Util\Transform.h"
#include "Texture.h"

class IGameObject
{
public:
	virtual ~IGameObject(); // Role: Delete the unique shader program belonging to it

	virtual void Draw(GLuint shader) = 0;
	virtual void Update() = 0;
	virtual void SetProgram(GLuint shaderName) = 0;
	virtual void Destroy() = 0;
	virtual GLuint GetProgram();

	
	virtual void SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture) = 0;
	virtual const GLuint GetTexture(const std::string&) const = 0;

protected:
	GLuint program = 0;
};

inline IGameObject::~IGameObject()
{
	if (program)
		glDeleteProgram(program);
}

inline GLuint IGameObject::GetProgram()
{
	return program;
}
