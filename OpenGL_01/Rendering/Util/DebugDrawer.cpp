#include "DebugDrawer.h"
#include <iostream>
#include "../../Managers/Shader_Factory.h"
#include "VboIndexer.h"


DebugDrawer::DebugDrawer()
{
	program = Shader_Factory::GetInstance()->CreateDebugProgram();
	MP = glGetUniformLocation(program, "MVP");
	transform = glGetUniformLocation(program, "TransformMatrix");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
}

DebugDrawer::~DebugDrawer()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	in_vertices.push_back(glm::vec3(from.getX(), from.getY(), from.getZ()));
	in_vertices.push_back(glm::vec3(to.getX(), to.getY(), to.getZ()));
	in_colors.push_back(glm::vec3(color.getX(), color.getY(), color.getZ()));
	in_colors.push_back(glm::vec3(color.getX(), color.getY(), color.getZ()));
}

void DebugDrawer::render()
{
	glUseProgram(program);
	VboIndexer::indexVBO(
		in_vertices,
		in_colors,
		indices,
		vertices);

	glm::mat4 ViewMatrix = Camera::GetViewMatrix();
	glm::mat4 ProjectionMatrix = Camera::GetProjectionMatrix();
	glm::mat4 mp = ProjectionMatrix * ViewMatrix;
	glBindVertexArray(vao);
	glUniformMatrix4fv(MP, 1, GL_FALSE, &mp[0][0]);
	glm::mat4 identity = glm::mat4(1.f);
	glUniformMatrix4fv(transform, 1, GL_FALSE, &identity[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(DVertexFormat) * vertices.size(),
		&vertices[0],
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned short) * indices.size(),
		&indices[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
		sizeof(DVertexFormat), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
		sizeof(DVertexFormat), 
		(void*)(offsetof(DVertexFormat, DVertexFormat::color)));

	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_SHORT, nullptr);

	glBindVertexArray(0);
}


void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{}

void DebugDrawer::reportErrorWarning(const char* warningString)
{
	std::cout << "ERROR IN BULLET: " << warningString << std::endl;
}

void DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{}

void DebugDrawer::setDebugMode(int debugMode)
{
	mode = debugMode;
}

int DebugDrawer::getDebugMode() const
{
	return mode;
}

void DebugDrawer::clearBuffers()
{
	vertices.clear();
	in_colors.clear();
	in_vertices.clear();
	indices.clear();
}
