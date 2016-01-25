#include "Quad.h"
#include "..\Util\Color.h"

Quad::Quad(Transform t, Color c): Model(t,c)
{
}

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

std::vector<VertexFormat> Quad::GetVertices()
{
	std::vector<VertexFormat> vertices;

	Vector3 c = this->transform.position;
	Vector3 scale = this->transform.scale;

	//TODO Implement Rotation
	vertices.push_back(VertexFormat(
		Vector3(c.x - scale.x * 50.0f, c.y + scale.y * 50.0f, 0),
		this->color));
	vertices.push_back(VertexFormat(
		Vector3(c.x + scale.x * 50.0f, c.y + scale.y * 50.0f, 0),
		this->color));
	vertices.push_back(VertexFormat(
		Vector3(c.x - scale.x * 50.0f, c.y - scale.y * 50.0f, 0),
		this->color));
	vertices.push_back(VertexFormat(
		Vector3(c.x + scale.x * 50.0f, c.y - scale.y * 50.0f, 0),
		this->color));

	return vertices;
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

