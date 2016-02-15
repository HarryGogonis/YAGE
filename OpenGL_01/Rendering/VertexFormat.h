#pragma once
#include "Util/Color.h"
#include <iostream>

struct VertexFormat
{
	glm::vec3 position; // first vertex attrib
	glm::vec2 uv;
	glm::vec4 color;

	VertexFormat(const glm::vec3 &inPos, const glm::vec2& inUV)
	{
		position = inPos;
		uv = inUV;
	}

	VertexFormat(const glm::vec4 &inPos, const Color inColor)
	{
		position = glm::vec3(inPos.x, inPos.y, inPos.z);
		color = inColor.toVec4();
	}

	friend std::ostream& operator<<(std::ostream& os, const VertexFormat& v) {
		os << "x:" << v.position.x << "\ty:" << v.position.y << "\tz:" << v.position.z << std::endl;
		return os;
	}

};