#pragma once
#include "glm\glm.hpp"

class Color
{
public:
	const static glm::vec4 RED;
	const static glm::vec4 GREEN;
	const static glm::vec4 BLUE;

	const static glm::vec4 Darken(glm::vec4 color, float percent);
	const static glm::vec4 Lighten(glm::vec4 color, float percent);
};