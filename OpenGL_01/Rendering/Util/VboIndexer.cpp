#include "VboIndexer.h"
#include "../VertexFormat.h"

/*
 * VBO Indexing
 * Source - https://github.com/opengl-tutorials/ogl/blob/master/common/vboindexer.cpp
 */

bool is_near(float v1, float v2) {
	return fabs(v1 - v2) < 0.01f;
}

bool getSimilarVertexIndex(
	glm::vec3 & in_vertex,
	glm::vec2 & in_uv,
	glm::vec3 & in_normal,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	unsigned short & result
	) {
	// Lame linear search
	for (unsigned int i = 0; i<out_vertices.size(); i++) {
		if (
			is_near(in_vertex.x, out_vertices[i].x) &&
			is_near(in_vertex.y, out_vertices[i].y) &&
			is_near(in_vertex.z, out_vertices[i].z) &&
			is_near(in_uv.x, out_uvs[i].x) &&
			is_near(in_uv.y, out_uvs[i].y) &&
			is_near(in_normal.x, out_normals[i].x) &&
			is_near(in_normal.y, out_normals[i].y) &&
			is_near(in_normal.z, out_normals[i].z)
			) {
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}

void VboIndexer::indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<unsigned short>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		unsigned short index;
		bool found = getSimilarVertexIndex(
			in_vertices[i], in_uvs[i], in_normals[i],
			out_vertices, out_uvs, out_normals,
			index);

		if (found)
		{
			out_indices.push_back(index);
		}
		else
		{
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back( (unsigned short)out_vertices.size() - 1);
		}
	}
}
