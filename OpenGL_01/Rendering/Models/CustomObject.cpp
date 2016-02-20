#include "CustomObject.h"
#include "../../Managers/Models_Manager.h"
#include "../Util/VboIndexer.h"
#include "SOIL.h"
#include <glm/gtx/string_cast.hpp>

CustomObject::CustomObject()
{
}

CustomObject::~CustomObject()
{
}

std::vector<VertexFormat> CustomObject::GetVertices()
{
	std::vector<VertexFormat> out;
	for (int i = 0; i < vertices.size(); i++)
	{
		out.push_back(
			VertexFormat(vertices[i], uvs[i])
		);
	}
	return out;
}

CustomObject::CustomObject(const std::string& objectPath, const std::string& texturePath)
{
	//TODO pass in transform
	this->transform = Transform(
		glm::vec3(0, 0, 0),
		glm::vec3(1, 1, 1),
		Quaternion());
	this->objectPath = objectPath;
	this->texturePath = texturePath;

	this->SetTexture(texturePath, SOIL_load_OGL_texture(
		texturePath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS));
}

void CustomObject::Update()
{
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();
	glm::mat4 translation = this->transform.getTranslationMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

	std::cout << glm::to_string(ModelMatrix) << std::endl;

	// Send transformation to currently bound shader
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void CustomObject::SetTexture(const std::string& textureName, GLuint texture)
{
	if (texture == 0) return;
	this->texturePath = textureName;
	textures[textureName] = texture;
}

void CustomObject::Draw()
{	
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture(texturePath));
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);

	// Draw triangles
	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
}

void CustomObject::Destroy()
{
	Model::Destroy();
}

void CustomObject::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;


	// Get handlers
	MatrixID = glGetUniformLocation(program, "MVP");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Read .obj file
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	Models_Manager::LoadObject(objectPath, temp_vertices, temp_uvs, temp_normals);
	
	// Generate VBO indices
	VboIndexer::indexVBO(temp_vertices, temp_uvs, temp_normals, indices, vertices, uvs, normals);
	std::vector<VertexFormat> vertices = GetVertices();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(VertexFormat) * vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned short) * indices.size(),
		&indices[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::uv)));
	glBindVertexArray(0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}
