#pragma once
#include "glm\glm.hpp"

struct VertexFormat
{
	glm::vec3 position; // first vertex attrib
	glm::vec4 color;

	VertexFormat(const glm::vec3 &inPos, const glm::vec4 &inColor)
	{
		position = inPos;
		color = inColor;
	}

	VertexFormat() {}
};