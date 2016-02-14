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
	glm::vec4 c = this->transform.position;
	glm::mat4 scale = this->transform.getScaleMatrix();
	glm::mat4 rotation = this->transform.getRotationMatrix();

	// Front
	glm::vec4 v1 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v2 = glm::vec4(c.x + bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v3 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v4 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v5 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v6 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	// Right
	glm::vec4 v7 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v8 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v9 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v10 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v11 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v12 = glm::vec4(c.x + bScale, c.y - bScale, c.z + bScale, 1);
	// Back
	glm::vec4 v13 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v14 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v15 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v16 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v17 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v18 = glm::vec4(c.x - bScale, c.y + bScale, c.z - bScale, 1);
	// Left
	glm::vec4 v19 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v20 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v21 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v22 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v23 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v24 = glm::vec4(c.x - bScale, c.y + bScale, c.z - bScale, 1);
	// Top
	glm::vec4 v25 = glm::vec4(c.x + bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v26 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v27 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v28 = glm::vec4(c.x - bScale, c.y + bScale, c.z + bScale, 1);
	glm::vec4 v29 = glm::vec4(c.x + bScale, c.y + bScale, c.z - bScale, 1);
	glm::vec4 v30 = glm::vec4(c.x - bScale, c.y + bScale, c.z - bScale, 1);
	// Bottom
	glm::vec4 v31 = glm::vec4(c.x - bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v32 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v33 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v34 = glm::vec4(c.x + bScale, c.y - bScale, c.z - bScale, 1);
	glm::vec4 v35 = glm::vec4(c.x - bScale, c.y - bScale, c.z + bScale, 1);
	glm::vec4 v36 = glm::vec4(c.x + bScale, c.y - bScale, c.z + bScale, 1);

	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 ModelMatrix = scale * rotation;
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	vertices.push_back(VertexFormat(v1, this->color));
	vertices.push_back(VertexFormat(v2, this->color));
	vertices.push_back(VertexFormat(v3, this->color));
	vertices.push_back(VertexFormat(v4, this->color));
	vertices.push_back(VertexFormat(v5, this->color));
	vertices.push_back(VertexFormat(v6, this->color));
	vertices.push_back(VertexFormat(v7, this->color));
	vertices.push_back(VertexFormat(v8, this->color));
	vertices.push_back(VertexFormat(v9, this->color));
	vertices.push_back(VertexFormat(v10, this->color));
	vertices.push_back(VertexFormat(v11, this->color));
	vertices.push_back(VertexFormat(v12, this->color));
	vertices.push_back(VertexFormat(v13, this->color));
	vertices.push_back(VertexFormat(v14, this->color));
	vertices.push_back(VertexFormat(v15, this->color));
	vertices.push_back(VertexFormat(v16, this->color));
	vertices.push_back(VertexFormat(v17, this->color));
	vertices.push_back(VertexFormat(v18, this->color));
	vertices.push_back(VertexFormat(v19, this->color));
	vertices.push_back(VertexFormat(v20, this->color));
	vertices.push_back(VertexFormat(v21, this->color));
	vertices.push_back(VertexFormat(v22, this->color));
	vertices.push_back(VertexFormat(v23, this->color));
	vertices.push_back(VertexFormat(v24, this->color));
	vertices.push_back(VertexFormat(v25, this->color));
	vertices.push_back(VertexFormat(v26, this->color));
	vertices.push_back(VertexFormat(v27, this->color));
	vertices.push_back(VertexFormat(v28, this->color));
	vertices.push_back(VertexFormat(v29, this->color));
	vertices.push_back(VertexFormat(v30, this->color));
	vertices.push_back(VertexFormat(v31, this->color));
	vertices.push_back(VertexFormat(v32, this->color));
	vertices.push_back(VertexFormat(v33, this->color));
	vertices.push_back(VertexFormat(v34, this->color));
	vertices.push_back(VertexFormat(v35, this->color));
	vertices.push_back(VertexFormat(v36, this->color));

	return vertices;
}

void Quad::Draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

