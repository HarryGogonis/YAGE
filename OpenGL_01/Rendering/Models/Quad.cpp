#include "Quad.h"
#include "..\Util\Color.h"

Quad::Quad()
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

	std::vector<VertexFormat> vertices;

	//TODO programmtically input vertex
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.5, 0.0), Color::Darken(Color::RED, 0.5)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.75, 0.0), Color::Darken(Color::RED, 0.5)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.5, 0.0), Color::Lighten(Color::RED, 0.5)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.75, 0.0), Color::Lighten(Color::RED, 0.5)));
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
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
	//TODO implement
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}