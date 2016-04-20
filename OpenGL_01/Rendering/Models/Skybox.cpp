#include "Skybox.h"
#include "../../Managers/Shader_Factory.h"
#include "../Util/Camera.h"
#include <SOIL.h>

const float SKYBOX_SIZE = 1;
Skybox* Skybox::mSkybox; // static instance for the singleton
Skybox* Skybox::GetInstance()
{
	if (mSkybox == nullptr)
		mSkybox = new Skybox();
	return mSkybox;
}


void Skybox::Draw()
{
	glDepthMask(GL_FALSE);
	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glUniform1i(Texture_ID, 0);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthMask(GL_TRUE);
	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthFuncMode);
}

void Skybox::Draw(GLuint)
{
	Draw();
}

void Skybox::Update()
{
	glUseProgram(program);
	glm::mat4 view = glm::mat4(glm::mat3(Camera::GetViewMatrix()));
	glm::mat4 proj = Camera::GetProjectionMatrix();

	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &proj[0][0]);
}

void Skybox::Destroy()
{
}

void Skybox::SetCubemap(const std::string& path)
{
	texture = SOIL_load_OGL_single_cubemap(
			path.c_str(),
			"EWUDNS",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS);
	if (!texture)
	{
		std::cout << "ERROR LOADING CUBEMAP" << SOIL_last_result() << std::endl;
	}
	else
	{
		std::cout << "loaded cubemap" << std::endl;
	}
}

Skybox::Skybox()
{
	Shader_Factory* shader_manager = Shader_Factory::GetInstance();
	SetProgram(shader_manager->CreateProgram(
		"skyboxShader",
		"Shaders\\SkyboxVertexShader.glsl",
		"Shaders\\SkyboxFragmentShader.glsl"));
	SetCubemap("Assets\\skybox.jpg");

	P_ID = glGetUniformLocation(program, "projection");
	V_ID = glGetUniformLocation(program, "view");
	Texture_ID = glGetUniformLocation(program, "skybox");

	static const GLfloat vertices[] = {
		-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE, // triangle 1 : begin
		-SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE, // triangle 1 : end
		SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE, // triangle 2 : begin
		-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE, // triangle 2 : end
		SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE,-SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		-SKYBOX_SIZE, SKYBOX_SIZE, SKYBOX_SIZE,
		SKYBOX_SIZE,-SKYBOX_SIZE, SKYBOX_SIZE
	};
	

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}
