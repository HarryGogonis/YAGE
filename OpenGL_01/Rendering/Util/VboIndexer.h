#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include "DebugDrawer.h"

class VboIndexer
{
public:
	static void indexVBO(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec3>& in_colors,
		std::vector<unsigned short>& out_indices,
		std::vector<DVertexFormat>& out_formats);
};

