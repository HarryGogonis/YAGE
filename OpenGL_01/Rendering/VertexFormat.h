#pragma once
#include "Util\Color.h"
#include <iostream>

struct VertexFormat
{
	glm::vec3 position; // first vertex attrib
	glm::vec4 color;

	VertexFormat(const glm::vec3 &inPos, const glm::vec4 &inColor)
	{
		position = inPos;
		color = inColor;
	}

	VertexFormat(const Vector3 &inPos, const Color &inColor)
	{
		position = inPos.toVec3();
		color = inColor.toVec4();
	}

	//VertexFormat() {}

	friend std::ostream& operator<<(std::ostream& os, const VertexFormat& v) {
		os << "x:" << v.position.x << "\ty:" << v.position.y << "\tz:" << v.position.z << std::endl;
		return os;
	}

};