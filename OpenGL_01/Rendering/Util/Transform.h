#pragma once
#include "Quaternion.h"
#include <glm/glm.hpp>

class Transform
{
public:
	glm::vec4 position, scale;
	Quaternion rotation;

	Transform();
	Transform(glm::vec4 position, glm::vec4 scale, Quaternion rotation);
	Transform(glm::vec3 position, glm::vec3 scale, Quaternion rotation);
	Transform(glm::vec4 position);

	glm::mat4 getTranslationMatrix() const;
	glm::mat4 getScaleMatrix() const;
	glm::mat4 getRotationMatrix();

	~Transform();
};