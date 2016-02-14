#include "Triangle.h"
#include "..\Util\Color.h"
#include "../Util/Camera.h"

Triangle::Triangle(Transform t, Color c): Model(t, c)
{}

Triangle::~Triangle() {} // use parent method

void Triangle::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices = GetVertices();

	/* std::cout << "============ Triangle1 ============" << std::endl;
	std::cout << vertices[0] << std::endl;
	std::cout << vertices[1] << std::endl;
	std::cout << vertices[2] << std::endl;
	std::cout << "===================================" << std::endl; */

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(void*)0);
	glEnableVertexAttribArray(1);
	// you can use offsetof to get the offset of an attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);

	//here we assign the values
	this->vao = vao;
	this->vbos.push_back(vbo);
}

void Triangle::Update()
{

}

void Triangle::Draw()
{
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();
	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUseProgram(program);
	GLuint MatrixID = glGetUniformLocation(program, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
 * Returns the 2D representation of the Model
 */
std::vector<VertexFormat> Triangle::GetVertices()
{
	std::vector<VertexFormat> vertices;
	glm::vec4 c = this->transform.position;

	/* base vertices */
	glm::vec4 v1 = glm::vec4(
		0.25f + c.x, 
		-0.25f + c.y,
		0.5f + c.z,
		1.0f);
	glm::vec4 v2 = glm::vec4(
		-0.25f + c.x,
		-0.25f + c.y,
		0.5f + c.z,
		1.0f);
	glm::vec4 v3 = glm::vec4(
		0.25f + c.x,
		0.25f + c.y,
		0.5f + c.z,
		1.0f);

	vertices.push_back(VertexFormat(v1, this->color));
	vertices.push_back(VertexFormat(v2, this->color));
	vertices.push_back(VertexFormat(v3, this->color));
	
	return vertices;
}