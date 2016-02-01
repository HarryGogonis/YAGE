#include "Triangle.h"
#include "..\Util\Color.h"
#include <iostream>

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
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
 * Returns the 2D representation of the Model
 */
std::vector<VertexFormat> Triangle::GetVertices()
{
	std::vector<VertexFormat> vertices;
	float bScale = 50.0;
	Vector3 c = this->transform.position;
	Matrix3 scale = this->transform.getScaleMatrix();
	Matrix3 rotation = this->transform.getRotationMatrix();

	std::cout << "c:\n" << c << std::endl;

	/* base vertices */
	Vector3 v1 = Vector3(
		c.x, 
		c.y + bScale / 0.8660254f,
		0.0f);
	Vector3 v2 = Vector3(
		c.x - bScale,
		c.y - bScale * 0.5773503f,
		0.0f);
	Vector3 v3 = Vector3(
		c.x + bScale,
		c.y - bScale * 0.5773503f,
		0.0f);

	/* rotate and scale vertices */
	v1 = rotation.dot(scale.dot(v1));
	v2 = rotation.dot(scale.dot(v2));
	v3 = rotation.dot(scale.dot(v3));

	vertices.push_back(VertexFormat(v1, this->color));
	vertices.push_back(VertexFormat(v2, this->color));
	vertices.push_back(VertexFormat(v3, this->color));
	
	return vertices;
}