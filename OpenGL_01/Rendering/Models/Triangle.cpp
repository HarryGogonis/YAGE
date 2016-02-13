#include "Triangle.h"
#include "..\Util\Color.h"
#include "..\Util\Camera.h"
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
	Vector4 c = this->transform.position;
	Matrix4 scale = this->transform.getScaleMatrix();
	Matrix4 rotation = this->transform.getRotationMatrix();
	Vector4 camV = Camera::GetInstance().transform.getRotationMatrix().dot(
		Camera::GetInstance().transform.position);

	std::cout << "c:\n" << c << std::endl;

	/* base vertices */
	Vector4 v1 = Vector4(
		c.x, 
		c.y + bScale / 0.8660254f,
		0.0f);
	Vector4 v2 = Vector4(
		c.x - bScale,
		c.y - bScale * 0.5773503f,
		0.0f);
	Vector4 v3 = Vector4(
		c.x + bScale,
		c.y - bScale * 0.5773503f,
		0.0f);

	/* rotate and scale vertices */
	Matrix4 m = scale * rotation;
	v1 = m.dot(v1) - camV;
	v2 = m.dot(v2) - camV;
	v3 = m.dot(v3) - camV;

	vertices.push_back(VertexFormat(v1, this->color));
	vertices.push_back(VertexFormat(v2, this->color));
	vertices.push_back(VertexFormat(v3, this->color));
	
	return vertices;
}