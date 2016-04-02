#pragma once
#include "GL/glew.h"

/*
 * Shadow Manager is a Singleton that hold the shadow map
 */
class Shadow_Manager
{
public:
	static Shadow_Manager* GetInstance();

	void SetProgram(GLuint);
	GLuint GetProgram() const;
	GLuint GetShadowMap() const;

	const static int DEPTH_TEXTURE_SIZE;

	void BindForWriting() const;
private:
	Shadow_Manager();
	static Shadow_Manager* mShadowManager;
	
	GLuint program;
	GLuint depth_texture, depth_fbo;
};
