#include "Cube.h"
#include "..\Util\Color.h"
#include "..\Util\Camera.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

Cube::Cube(Transform t): Model(t)
{}

Cube::~Cube()
{}

void Cube::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	
	this->MatrixID = glGetUniformLocation(program, "MVP");
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices = GetVertices();
	std::vector<unsigned short> indices = GetIndices();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(VertexFormat) * vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
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
	
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}

void Cube::Update()
{
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
	
	// Send MVP transformation to currently bound shader
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

std::vector<VertexFormat> Cube::GetVertices()
{
	std::vector<VertexFormat> vertices;
	float bScale = .5;
	glm::vec4 c = this->transform.position;
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();

	// Front
	glm::vec3 v1 = glm::vec3(c.x - bScale, c.y - bScale, c.z + bScale);
	glm::vec3 v2 = glm::vec3(c.x + bScale, c.y - bScale, c.z + bScale);
	glm::vec3 v3 = glm::vec3(c.x + bScale, c.y + bScale, c.z + bScale);
	glm::vec3 v4 = glm::vec3(c.x - bScale, c.y + bScale, c.z + bScale);

	// Right
	glm::vec3 v5 = glm::vec3(c.x + bScale, c.y + bScale, c.z + bScale);
	glm::vec3 v6 = glm::vec3(c.x + bScale, c.y + bScale, c.z - bScale);
	glm::vec3 v7 = glm::vec3(c.x + bScale, c.y - bScale, c.z - bScale);
	glm::vec3 v8 = glm::vec3(c.x + bScale, c.y + bScale, c.z + bScale);
	
	// Back
	glm::vec3 v9 = glm::vec3(c.x - bScale, c.y - bScale, c.z - bScale);
	glm::vec3 v10 = glm::vec3(c.x + bScale, c.y - bScale, c.z - bScale);
	glm::vec3 v11 = glm::vec3(c.x + bScale, c.y + bScale, c.z - bScale);
	glm::vec3 v12 = glm::vec3(c.x - bScale, c.y - bScale, c.z - bScale);
	
	// Left
	glm::vec3 v13 = glm::vec3(c.x - bScale, c.y - bScale, c.z - bScale);
	glm::vec3 v14 = glm::vec3(c.x - bScale, c.y - bScale, c.z + bScale);
	glm::vec3 v15 = glm::vec3(c.x - bScale, c.y + bScale, c.z + bScale);
	glm::vec3 v16 = glm::vec3(c.x - bScale, c.y - bScale, c.z - bScale);
	
	// Top
	glm::vec3 v17 = glm::vec3(c.x + bScale, c.y + bScale, c.z + bScale);
	glm::vec3 v18 = glm::vec3(c.x - bScale, c.y + bScale, c.z + bScale);
	glm::vec3 v19 = glm::vec3(c.x + bScale, c.y + bScale, c.z - bScale);
	glm::vec3 v20 = glm::vec3(c.x - bScale, c.y + bScale, c.z + bScale);
	
	// Bottom
	glm::vec3 v21 = glm::vec3(c.x - bScale, c.y - bScale, c.z - bScale);
	glm::vec3 v22 = glm::vec3(c.x + bScale, c.y - bScale, c.z - bScale);
	glm::vec3 v23 = glm::vec3(c.x - bScale, c.y - bScale, c.z + bScale);
	glm::vec3 v24 = glm::vec3(c.x + bScale, c.y - bScale, c.z - bScale);

	vertices.push_back(VertexFormat(v1, glm::vec2(0,0)));
	vertices.push_back(VertexFormat(v2, glm::vec2(1,0)));
	vertices.push_back(VertexFormat(v3, glm::vec2(1,1)));
	vertices.push_back(VertexFormat(v4, glm::vec2(0,1)));

	vertices.push_back(VertexFormat(v5, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(v6, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(v7, glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(v8, glm::vec2(0, 1)));

	vertices.push_back(VertexFormat(v9, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(v10, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(v11, glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(v12, glm::vec2(0, 1)));

	vertices.push_back(VertexFormat(v13, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(v14, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(v15, glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(v16, glm::vec2(0, 1)));

	vertices.push_back(VertexFormat(v17, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(v18, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(v19, glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(v20, glm::vec2(0, 1)));

	vertices.push_back(VertexFormat(v21, glm::vec2(0, 0)));
	vertices.push_back(VertexFormat(v22, glm::vec2(1, 0)));
	vertices.push_back(VertexFormat(v23, glm::vec2(1, 1)));
	vertices.push_back(VertexFormat(v24, glm::vec2(0, 1)));
	return vertices;
}

std::vector<unsigned short> Cube::GetIndices()
{
	return { 0, 1, 2, 0, 2, 3, //front
		4, 5, 6, 4, 6, 7, //right
		8, 9, 10, 8, 10, 11, //back
		12, 13, 14, 12, 14, 15, //left
		16, 17, 18, 16, 18, 19, //upper
		20, 21, 22, 20, 22, 23 }; //bottom
}

void Cube::SetTexture(const std::string& textureName, GLuint texture)
{
	if (texture == 0) return;
	this->textureName = textureName;
	textures[textureName] = texture;
}

void Cube::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->GetTexture(textureName));
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

