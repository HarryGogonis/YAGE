#pragma once
#include "GL/glew.h"
#include "../Rendering/Util/Light.h"
#include "Shader_Factory.h"

/*
 * Shadow Manager is a Singleton that hold the shadow map
 * http://ogldev.atspace.co.uk/www/tutorial43/tutorial43.html
 */
class Shadow_Manager
{
public:
	static Shadow_Manager* GetInstance();

	//GLuint GetProgram() const;
	GLuint GetShadowMap() const;

	glm::mat4 GetDepthMatrix() const;
	void SetDepthMatrix(glm::mat4);

	const static int DEPTH_TEXTURE_SIZE;

	void BindForWriting() const;
	void Unbind() const;
private:
	Shadow_Manager();
	static Shadow_Manager* mShadowManager;
	Shader_Factory* mShaderFactory = Shader_Factory::GetInstance();

	glm::mat4 depth_matrix;
	
	GLuint depth_texture, depth_fbo;
};
