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
	//Camera::ComputeMatrices();
	//const Camera& camera = Camera::GetInstance();
	//camera.transform.position.x = camera.transform.position.x + 1;
	transform.rotation.x = transform.rotation.x < 1 ? transform.rotation.x + 0.005 : 0.0;
	transform.rotation.y = transform.rotation.y < 1 ? transform.rotation.y + 0.005 : 0.0;
	transform.rotation.z = transform.rotation.z < 1 ? transform.rotation.z + 0.005 : 0.0;
	std::vector<VertexFormat> vertices = GetVertices();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
}

std::vector<VertexFormat> Quad::GetVertices()
{
	std::vector<VertexFormat> vertices;
	float bScale = 50.0;
	Vector4 c = this->transform.position;
	Matrix4 scale = this->transform.getScaleMatrix();
	Matrix4 rotation = this->transform.getRotationMatrix();

	// Front
	Vector4 v1 = Vector4(c.x - bScale, c.y - bScale, c.z + bScale);
	Vector4 v2 = Vector4(c.x + bScale, c.y - bScale, c.z + bScale);
	Vector4 v3 = Vector4(c.x + bScale, c.y + bScale, c.z + bScale);
	Vector4 v4 = Vector4(c.x - bScale, c.y + bScale, c.z + bScale);
	Vector4 v5 = Vector4(c.x + bScale, c.y + bScale, c.z + bScale);
	Vector4 v6 = Vector4(c.x - bScale, c.y - bScale, c.z + bScale);
	// Right
	Vector4 v7 = Vector4(c.x + bScale, c.y + bScale, c.z + bScale);
	Vector4 v8 = Vector4(c.x + bScale, c.y + bScale, c.z - bScale);
	Vector4 v9 = Vector4(c.x + bScale, c.y - bScale, c.z - bScale);
	Vector4 v10 = Vector4(c.x + bScale, c.y + bScale, c.z + bScale);
	Vector4 v11 = Vector4(c.x + bScale, c.y - bScale, c.z - bScale);
	Vector4 v12 = Vector4(c.x + bScale, c.y - bScale, c.z + bScale);
	// Back
	Vector4 v13 = Vector4(c.x - bScale, c.y - bScale, c.z - bScale);
	Vector4 v14 = Vector4(c.x + bScale, c.y - bScale, c.z - bScale);
	Vector4 v15 = Vector4(c.x + bScale, c.y + bScale, c.z - bScale);
	Vector4 v16 = Vector4(c.x - bScale, c.y - bScale, c.z - bScale);
	Vector4 v17 = Vector4(c.x + bScale, c.y + bScale, c.z - bScale);
	Vector4 v18 = Vector4(c.x - bScale, c.y + bScale, c.z - bScale);
	// Left
	Vector4 v19 = Vector4(c.x - bScale, c.y - bScale, c.z - bScale);
	Vector4 v20 = Vector4(c.x - bScale, c.y - bScale, c.z + bScale);
	Vector4 v21 = Vector4(c.x - bScale, c.y + bScale, c.z + bScale);
	Vector4 v22 = Vector4(c.x - bScale, c.y - bScale, c.z - bScale);
	Vector4 v23 = Vector4(c.x - bScale, c.y + bScale, c.z + bScale);
	Vector4 v24 = Vector4(c.x - bScale, c.y + bScale, c.z - bScale);
	// Top
	Vector4 v25 = Vector4(c.x + bScale, c.y + bScale, c.z + bScale);
	Vector4 v26 = Vector4(c.x - bScale, c.y + bScale, c.z + bScale);
	Vector4 v27 = Vector4(c.x + bScale, c.y + bScale, c.z - bScale);
	Vector4 v28 = Vector4(c.x - bScale, c.y + bScale, c.z + bScale);
	Vector4 v29 = Vector4(c.x + bScale, c.y + bScale, c.z - bScale);
	Vector4 v30 = Vector4(c.x - bScale, c.y + bScale, c.z - bScale);
	// Bottom
	Vector4 v31 = Vector4(c.x - bScale, c.y - bScale, c.z - bScale);
	Vector4 v32 = Vector4(c.x + bScale, c.y - bScale, c.z - bScale);
	Vector4 v33 = Vector4(c.x - bScale, c.y - bScale, c.z + bScale);
	Vector4 v34 = Vector4(c.x + bScale, c.y - bScale, c.z - bScale);
	Vector4 v35 = Vector4(c.x - bScale, c.y - bScale, c.z + bScale);
	Vector4 v36 = Vector4(c.x + bScale, c.y - bScale, c.z + bScale);

	Matrix4 ViewMatrix = Camera::GetViewMatrix();
	Matrix4 ProjectionMatrix = Camera::GetProjectionMatrix();
	Matrix4 ModelMatrix = scale * rotation;
	Matrix4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	vertices.push_back(VertexFormat(MVP.dot(v1), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v2), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v3), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v4), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v5), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v6), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v7), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v8), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v9), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v10), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v11), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v12), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v13), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v14), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v15), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v16), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v17), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v18), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v19), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v20), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v21), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v22), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v23), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v24), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v25), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v26), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v27), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v28), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v29), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v30), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v31), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v32), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v33), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v34), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v35), this->color));
	vertices.push_back(VertexFormat(MVP.dot(v36), this->color));

	return vertices;
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

