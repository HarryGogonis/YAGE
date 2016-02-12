#include "Quad.h"
#include "..\Util\Color.h"
#include "../Util/Camera.h"

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
	std::cout << "UPDATE CALLED" << std::endl;
//	transform.rotation.x = transform.rotation.x > 1 ? 0 : transform.rotation.x + 0.001;
	transform.rotation.y = transform.rotation.y > 1 ? 0 : transform.rotation.y + 0.001;
//	transform.rotation.z = transform.rotation.z > 1 ? 0 : transform.rotation.z + 0.001;
	std::vector<VertexFormat> vertices = GetVertices();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);

	
}

std::vector<VertexFormat> Quad::GetVertices()
{
	std::vector<VertexFormat> vertices;
	float bScale = 50.0;
	Vector4 c = this->transform.position;
	Matrix4 scale = this->transform.getScaleMatrix();
	Matrix4 rotation = this->transform.getRotationMatrix();
	Camera camera = Camera::GetInstance();

	Vector4 v1 = Vector4(c.x - bScale, c.y + bScale, 0);
	Vector4 v2 = Vector4(c.x + bScale, c.y + bScale, 0);
	Vector4 v3 = Vector4(c.x - bScale, c.y - bScale, 0);
	Vector4 v4 = Vector4(c.x + bScale, c.y - bScale, 0);

	v1 = rotation.dot(scale.dot(v1));
	v2 = rotation.dot(scale.dot(v2));
	v3 = rotation.dot(scale.dot(v3));
	v4 = rotation.dot(scale.dot(v4));

	vertices.push_back(VertexFormat(v1, this->color));
	vertices.push_back(VertexFormat(v2, this->color));
	vertices.push_back(VertexFormat(v3, this->color));
	vertices.push_back(VertexFormat(v4, this->color));
	return vertices;
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

