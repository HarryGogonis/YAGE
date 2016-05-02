#pragma once
#include "GL/glew.h"
#include "../Rendering/Util/Light.h"
#include "Shader_Factory.h"

/**********************************************************************************************//**
 * @class	Shadow_Manager
 *
 * @brief	Manager for shadows implemented as a Singleton.
 *
 * @author	Harry Gogonis
 **************************************************************************************************/

class Shadow_Manager
{
public:

	/**********************************************************************************************//**
	 * @fn	static Shadow_Manager* Shadow_Manager::GetInstance();
	 *
	 * @brief	Gets the instance
	 *
	 * @author	Harry
	 *
	 * @return	The Singleton instance
	 **************************************************************************************************/

	static Shadow_Manager* GetInstance();

	/**********************************************************************************************//**
	 * @fn	GLuint Shadow_Manager::GetShadowMap() const;
	 *
	 * @brief	Gets shadow map texture.
	 *
	 * @return	The shadow map.
	 **************************************************************************************************/

	GLuint GetShadowMap() const;

	/**********************************************************************************************//**
	 * @fn	glm::mat4 Shadow_Manager::GetDepthMatrix() const;
	 *
	 * @brief	Gets the 4x4 depth matrix.
	 *
	 * @return	The depth matrix.
	 **************************************************************************************************/

	glm::mat4 GetDepthMatrix() const;

	/**********************************************************************************************//**
	 * @fn	void Shadow_Manager::SetDepthMatrix(glm::mat4 DepthMatrix);
	 *
	 * @brief	Sets the depth matrix.
	 *
	 * @param	DepthMatrix	The depth matrix.
	 **************************************************************************************************/

	void SetDepthMatrix(glm::mat4 DepthMatrix);

	/** @brief	Size of the depth texture in pixels. */
	const static int DEPTH_TEXTURE_SIZE;

	/**********************************************************************************************//**
	 * @fn	void Shadow_Manager::BindForWriting() const;
	 *
	 * @brief	Bind the depth t exture for writing.
	 **************************************************************************************************/

	void BindForWriting() const;

	/**********************************************************************************************//**
	 * @fn	void Shadow_Manager::Unbind() const;
	 *
	 * @brief	Unbinds the depth texture
	 **************************************************************************************************/

	void Unbind() const;
private:
	Shadow_Manager();
	/** @brief Singleton instance */
	static Shadow_Manager* mShadowManager;
	Shader_Factory* mShaderFactory = Shader_Factory::GetInstance();

	glm::mat4 depth_matrix;
	
	GLuint depth_texture, depth_fbo;
};
