#pragma once
#include <vector>
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"

#include "Util\Transform.h"

class IGameObject
{
public:
	virtual ~IGameObject() = 0;

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void SetProgram(GLuint shaderName) = 0;
	virtual void Destroy() = 0;

	
	virtual void SetTexture(const std::string&, GLuint) = 0;
	virtual const GLuint GetTexture(const std::string&) const = 0;
};

inline IGameObject::~IGameObject()
{

}
