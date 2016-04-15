#pragma once
#include <vector>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Util\Transform.h"
#include "Texture.h"
#include "btBulletDynamicsCommon.h"

/**********************************************************************************************//**
 * @class	IGameObject
 *
 * @brief	A Game Object. All objects that are to be rendered will inherit this class.
 **************************************************************************************************/

class IGameObject
{
public:

	/**********************************************************************************************//**
	 * @fn	virtual IGameObject::~IGameObject();
	 *
	 * @brief	Destructor that deletes the unique shader program and shadow program belonging to the object.
	 **************************************************************************************************/

	virtual ~IGameObject(); // Role: Delete the unique shader program belonging to it

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::Draw(GLuint shader) = 0;
	 *
	 * @brief	Draws via the given shader.
	 *
	 * @param	shader	The shader.
	 **************************************************************************************************/

	virtual void Draw(GLuint shader) = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::DrawShadow(GLuint shader) = 0;
	 *
	 * @brief	Draw shadows via the given shader.
	 **************************************************************************************************/

	virtual void DrawShadow(GLuint shader) = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::Update() = 0;
	 *
	 * @brief	Updates this object.
	 **************************************************************************************************/

	virtual void Update() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::Destroy() = 0;
	 *
	 * @brief	Destroys this object.
	 **************************************************************************************************/

	virtual void Destroy() = 0;

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::SetProgram(GLuint shaderName);
	 *
	 * @brief	Sets the main shader program corresponding to this object.
	 *
	 * @author	Harry
	 * @date	4/14/2016
	 *
	 * @param	shaderName	Name of the shader.
	 **************************************************************************************************/

	virtual void SetProgram(GLuint shaderName);

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::SetShadowProgram(GLuint shaderName);
	 *
	 * @brief	Sets the shadow pass shader program corresponding to this object.
	 *
	 * @param	shaderName	Name of the shader.
	 **************************************************************************************************/

	virtual void SetShadowProgram(GLuint shaderName);

	/**********************************************************************************************//**
	 * @fn	virtual GLuint IGameObject::GetProgram();
	 *
	 * @brief	Gets the object's main shader program.
	 *
	 * @return	The main shader program.
	 **************************************************************************************************/

	virtual GLuint GetProgram();

	/**********************************************************************************************//**
	 * @fn	virtual GLuint IGameObject::GetShadowProgram();
	 *
	 * @brief	Gets the object's shadow program.
	 *
	 * @return	The shadow program.
	 **************************************************************************************************/

	virtual GLuint GetShadowProgram();

	/**********************************************************************************************//**
	 * @fn	virtual void IGameObject::SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture) = 0;
	 *
	 * @brief	Adds a texture to an object
	 *
	 * @param	textureName	Name of the texture.
	 * @param	textureType	Type of the texture.
	 * @param	texture	   	The texture id.
	 **************************************************************************************************/

	virtual void SetTexture(const std::string& textureName, const TextureType& textureType, const GLuint& texture) = 0;

	/**********************************************************************************************//**
	 * @fn	virtual const GLuint IGameObject::GetTexture(const std::string& textureName) const = 0;
	 *
	 * @brief	Gets a texture.
	 *
	 * @param	textureName	The name of the texture.
	 *
	 * @return	The texture.
	 **************************************************************************************************/

	virtual const GLuint GetTexture(const std::string& textureName) const = 0;

protected:
	GLuint program = 0;
	GLuint shadowProgram = 0;
};

inline IGameObject::~IGameObject()
{
	if (program)
		glDeleteProgram(program);
	if (shadowProgram)
		glDeleteProgram(shadowProgram);
}

inline GLuint IGameObject::GetProgram()
{
	return program;
}

inline GLuint IGameObject::GetShadowProgram()
{
	return shadowProgram;
}

inline void IGameObject::SetProgram(GLuint p)
{
	program = p;
}

inline void IGameObject::SetShadowProgram(GLuint p)
{
	shadowProgram = p;
}

