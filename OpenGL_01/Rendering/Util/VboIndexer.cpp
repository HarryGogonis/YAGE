#include "VboIndexer.h"

/*
 * VBO Indexing
 * Source - https://github.com/opengl-tutorials/ogl/blob/master/common/vboindexer.cpp
 */

bool is_near(float v1, float v2) {
	return fabs(v1 - v2) < 0.01f;
}

bool getSimilarVertexIndex(
	glm::vec3 & in_vertex,
	glm::vec3 & in_color,
	std::vector<DVertexFormat>& out_formats,
	unsigned short & result
	) {
	// Lame linear search
	for (unsigned int i = 0; i < out_formats.size(); i++) {
		if (
			is_near(in_vertex.x, out_formats[i].position.x) &&
			is_near(in_vertex.y, out_formats[i].position.y) &&
			is_near(in_vertex.z, out_formats[i].position.z) &&
			is_near(in_color.x, out_formats[i].color.x) &&
			is_near(in_color.y, out_formats[i].color.y) &&
			is_near(in_color.z, out_formats[i].color.z)
			) {
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}

void VboIndexer::indexVBO(
	std::vector<glm::vec3>& in_vertices, 
	std::vector<glm::vec3>& in_colors, 
	std::vector<unsigned short>& out_indices, 
	std::vector<DVertexFormat>& out_formats)
{
	for (unsigned int i = 0; i < in_vertices.size(); i++)
	{
		unsigned short index;
		bool found = getSimilarVertexIndex(
			in_vertices[i], in_colors[i],
			out_formats,
			index);

		if (found)
		{
			out_indices.push_back(index);
		}
		else
		{
			out_formats.push_back(DVertexFormat(in_vertices[i], in_colors[i]));
			out_indices.push_back( (unsigned short)out_formats.size() - 1);
		}
	}
}
