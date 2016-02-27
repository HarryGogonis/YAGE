#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
	glm::vec3 position, scale;
	glm::quat rotation;

	Transform();
	Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation);

	void SetScale(const glm::vec3 &scale);
	void SetPosition(const glm::vec3 &position);
	void SetRotation(float angle, glm::vec3 axis);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	glm::mat4 getTranslationMatrix() const;
	glm::mat4 getScaleMatrix() const;
	glm::mat4 getRotationMatrix() const;
	glm::mat4 getTransformMatrix() const;

	~Transform();
};