#pragma once
#include "Util/Color.h"
#include <iostream>

struct VertexFormat
{
	glm::vec3 position; // first vertex attrib
	glm::vec2 uv;

	VertexFormat(const glm::vec3 &inPos, const glm::vec2& inUV)
	{
		position = inPos;
		uv = inUV;
	}

	friend std::ostream& operator<<(std::ostream& os, const VertexFormat& v) {
		os << "x:" << v.position.x << "\ty:" << v.position.y << "\tz:" << v.position.z << std::endl;
		return os;
	}

	bool operator<(const VertexFormat that) const {
		return memcmp((void*) this, (void*)&that, sizeof(VertexFormat))>0;
	}

};