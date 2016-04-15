#include "Shadow_Manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

const int Shadow_Manager::DEPTH_TEXTURE_SIZE = 1024; // ??? Hardcode ???
Shadow_Manager* Shadow_Manager::mShadowManager; // static instance for the singleton

Shadow_Manager* Shadow_Manager::GetInstance()
{
	if (mShadowManager == nullptr)
		mShadowManager = new Shadow_Manager();
	return mShadowManager;
}

GLuint Shadow_Manager::GetShadowMap() const
{
	return depth_texture;
}

glm::mat4 Shadow_Manager::GetDepthMatrix() const
{
	return depth_matrix;
}

void Shadow_Manager::SetDepthMatrix(glm::mat4 depth_matrix)
{
	this->depth_matrix = depth_matrix;
}

void Shadow_Manager::BindForWriting() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
}

void Shadow_Manager::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Shadow_Manager::Shadow_Manager()
{
	// Create a depth texture
	glGenTextures(1, &depth_texture);
	glBindTexture(GL_TEXTURE_2D, depth_texture);

	// Allocate storage for the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
		DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	// Set the default filtering modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set up depth comparison mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	// Set up wrapping modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0); //WARNING

	// Create FBO to render depth into
	glGenFramebuffers(1, &depth_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);

	// Attach depth texture to frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depth_texture, 0);

	// Disable color rendering on frame buffer
	glDrawBuffer(GL_NONE);

	// Check that framebuffer is okay
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR: Framebuffer not okay" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
