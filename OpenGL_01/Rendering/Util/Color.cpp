#include "Color.h"

const glm::vec4 Color::RED		= glm::vec4(1, 0, 0, 1);
const glm::vec4 Color::GREEN	= glm::vec4(0, 1, 0, 1);
const glm::vec4 Color::BLUE		= glm::vec4(0, 0, 1, 1);

const glm::vec4 Color::Darken(glm::vec4 color, float percent)
{
	float n = 1 - percent;
	return color * glm::vec4(n, n, n, 1);
}

const glm::vec4 Color::Lighten(glm::vec4 color, float percent)
{
	return color + glm::vec4(percent, percent, percent, 0);
}

