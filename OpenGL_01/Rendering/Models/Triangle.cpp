#include "Triangle.h"
#include "..\Util\Color.h"

Triangle::Triangle() {} 
Triangle::~Triangle() {} // use parent method

void Triangle::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	//TODO programmtically input vertex
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0), Color(1,0,0)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0), Color::GREEN));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0), Color::BLUE));

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
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}