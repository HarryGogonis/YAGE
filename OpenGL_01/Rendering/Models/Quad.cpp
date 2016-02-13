#include "Quad.h"
#include "..\Util\Color.h"
#include "..\Util\Camera.h"

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
	//const Camera& camera = Camera::GetInstance();
	//camera.transform.position.x = camera.transform.position.x + 1;
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
	const Camera& camera = Camera::GetInstance();

	Vector4 v1 = Vector4(c.x - bScale, c.y + bScale, 0);
	Vector4 v2 = Vector4(c.x + bScale, c.y + bScale, 0);
	Vector4 v3 = Vector4(c.x - bScale, c.y - bScale, 0);
	Vector4 v4 = Vector4(c.x + bScale, c.y - bScale, 0);

	Vector4 camV = camera.transform.getRotationMatrix().dot(camera.transform.position);
	std::cout << "camV\t" << camV << std::endl;

	/* TODO - Camera effects position
		* Camera is like a global rotation/translation 
		* Idea: m = (rotation - cameraRotation) * scale * cameraTranslation
		*
		*/
	
	Matrix4 m = scale * rotation * camera.transform.getRotationMatrix();
	v1 = m.dot(v1 - camera.transform.position);
	v2 = m.dot(v2 - camV);
	v3 = m.dot(v3) - camV;
	v4 = m.dot(v4) - camV;

	std::cout << "V1: " << v1 << std::endl;
	
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

