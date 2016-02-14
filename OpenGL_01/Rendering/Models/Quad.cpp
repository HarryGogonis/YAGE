#include "Quad.h"
#include "..\Util\Color.h"
#include "..\Util\Camera.h"
#include <glm/glm.hpp>

Quad::Quad(Transform t, Color c): Model(t,c)
{}

Quad::~Quad()
{}

// Quad is just like a triangle but add 4th vertex and 
// draw arrays now uses GL_TRIANGLE_STRIP
void Quad::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices = GetVertices();

	/* std::cout << "============ Quad1 ============" << std::endl;
	std::cout << vertices[0] << std::endl;
	std::cout << vertices[1] << std::endl;
	std::cout << vertices[2] << std::endl;
	std::cout << vertices[3] << std::endl;
	std::cout << "===================================" << std::endl; */
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), nullptr);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
}

void Quad::Update()
{
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUseProgram(program);
	GLuint MatrixID = glGetUniformLocation(program, "MVP");// We don't need to get the handle every time
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	std::vector<VertexFormat> vertices = GetVertices();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

std::vector<VertexFormat> Quad::GetVertices()
{
	std::vector<VertexFormat> vertices;
	float bScale = .5;
	glm::vec4 c = this->transform.position;
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();

	// Front
	glm::vec4 v1 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v2 = glm::vec4(c.x + bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v3 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v4 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v5 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v6 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	// Right
	glm::vec4 v7 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v8 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v9 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v10 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v11 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v12 = glm::vec4(c.x + bScale, c.y - bScale, c.z + bScale, 1);
	// Back
	glm::vec4 v13 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v14 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v15 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v16 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v17 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v18 = glm::vec4(c.x - bScale, c.y + bScale, c.z - bScale, 1);
	// Left
	glm::vec4 v19 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v20 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v21 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v22 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v23 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v24 = glm::vec4(c.x - bScale, c.y + bScale, c.z - bScale, 1);
	// Top
	glm::vec4 v25 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v26 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v27 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v28 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v29 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v30 = glm::vec4(c.x - bScale, c.y + bScale, c.z - bScale, 1);
	// Bottom
	glm::vec4 v31 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v32 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v33 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v34 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v35 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v36 = glm::vec4(c.x + bScale, c.y - bScale, c.z + bScale, 1);

	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	vertices.push_back(VertexFormat(v1, this->color));
	vertices.push_back(VertexFormat(v2, this->color));
	vertices.push_back(VertexFormat(v3, this->color));
	vertices.push_back(VertexFormat(v4, this->color));
	vertices.push_back(VertexFormat(v5, this->color));
	vertices.push_back(VertexFormat(v6, this->color));
	vertices.push_back(VertexFormat(v7, Color::BLUE));
	vertices.push_back(VertexFormat(v8, Color::BLUE));
	vertices.push_back(VertexFormat(v9, Color::BLUE));
	vertices.push_back(VertexFormat(v10, Color::BLUE));
	vertices.push_back(VertexFormat(v11, Color::BLUE));
	vertices.push_back(VertexFormat(v12, Color::BLUE));
	vertices.push_back(VertexFormat(v13, Color::GREEN));
	vertices.push_back(VertexFormat(v14, Color::GREEN));
	vertices.push_back(VertexFormat(v15, Color::GREEN));
	vertices.push_back(VertexFormat(v16, Color::GREEN));
	vertices.push_back(VertexFormat(v17, Color::GREEN));
	vertices.push_back(VertexFormat(v18, Color::GREEN));
	vertices.push_back(VertexFormat(v19, Color::CYAN));
	vertices.push_back(VertexFormat(v20, Color::CYAN));
	vertices.push_back(VertexFormat(v21, Color::CYAN));
	vertices.push_back(VertexFormat(v22, Color::CYAN));
	vertices.push_back(VertexFormat(v23, Color::CYAN));
	vertices.push_back(VertexFormat(v24, Color::CYAN));
	vertices.push_back(VertexFormat(v25, Color::MAGENTA));
	vertices.push_back(VertexFormat(v26, Color::MAGENTA));
	vertices.push_back(VertexFormat(v27, Color::MAGENTA));
	vertices.push_back(VertexFormat(v28, Color::MAGENTA));
	vertices.push_back(VertexFormat(v29, Color::MAGENTA));
	vertices.push_back(VertexFormat(v30, Color::MAGENTA));
	vertices.push_back(VertexFormat(v31, Color::GRAY));
	vertices.push_back(VertexFormat(v32, Color::GRAY));
	vertices.push_back(VertexFormat(v33, Color::GRAY));
	vertices.push_back(VertexFormat(v34, Color::GRAY));
	vertices.push_back(VertexFormat(v35, Color::GRAY));
	vertices.push_back(VertexFormat(v36, Color::GRAY));

	return vertices;
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

