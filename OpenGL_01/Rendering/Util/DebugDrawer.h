#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "LinearMath/btIDebugDraw.h"


struct DVertexFormat
{
	glm::vec3 position;
	glm::vec3 color;

	DVertexFormat(const glm::vec3& inPos, const glm::vec3& inColor)
	{
		position = inPos;
		color = inColor;
	}
};

class DebugDrawer :
	public btIDebugDraw
{
public:
	DebugDrawer();
	~DebugDrawer();

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
	void reportErrorWarning(const char* warningString) override;
	void draw3dText(const btVector3& location, const char* textString) override;
	void setDebugMode(int debugMode) override;
	int getDebugMode() const override;

	void clearBuffers();
	void render();
private:
	GLuint	program,
			MP,
			transform,
			vao = 0,
			vbo = 0,
			ibo = 0;
	int mode;
	std::vector<DVertexFormat> vertices;
	std::vector<unsigned short> indices;

	std::vector<glm::vec3> in_vertices;
	std::vector<glm::vec3> in_colors;
};