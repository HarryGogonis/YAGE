#include "Triangle.h"
#include "..\Util\Color.h"
#include <iostream>

Triangle::Triangle(Transform t, Color c) {
	this->transform = t;
	this->color = c;
}
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
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::vector<VertexFormat> Triangle::GetVertices()
{
	std::vector<VertexFormat> vertices;

	Vector3 c = this->transform.position;
	Vector3 scale = this->transform.scale;
	//TODO Equallateral triangle w/ no rotation
	Vector3 x1 = Vector3(c.x * scale.x, (c.y + scale.y * 57.74f), 0.0f);
	Vector3 x2 = Vector3(c.x - scale.x * 50.0f, c.y - scale.y * 28.87f, 0.0f);
	Vector3 x3 = Vector3(c.x + scale.x * 50.0f, c.y - scale.y * 28.87f, 0.0f);

	vertices.push_back(VertexFormat(x1, Color::RED));
	vertices.push_back(VertexFormat(x2, this->color));
	vertices.push_back(VertexFormat(x3, this->color));
	
	return vertices;
}