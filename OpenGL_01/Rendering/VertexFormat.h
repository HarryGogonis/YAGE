#pragma once
#include <iostream>

/**********************************************************************************************//**
 * @struct	VertexFormat
 *
 * @brief	The vertex buffer format that is sent directly to the shader.
 **************************************************************************************************/

struct VertexFormat
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	VertexFormat(const glm::vec3 &inPos, const glm::vec2& inUV, const  glm::vec3& inNormal, const glm::vec3& inTangent, const glm::vec3& inBitangent)
	{
		position = inPos;
		uv = inUV;
		normal = inNormal;
		tangent = inTangent;
		bitangent = inBitangent;
	}

	friend std::ostream& operator<<(std::ostream& os, const VertexFormat& v) {
		os << "x:" << v.position.x << "\ty:" << v.position.y << "\tz:" << v.position.z << std::endl;
		return os;
	}

	bool operator<(const VertexFormat that) const {
		return memcmp((void*) this, (void*)&that, sizeof(VertexFormat))>0;
	}

};