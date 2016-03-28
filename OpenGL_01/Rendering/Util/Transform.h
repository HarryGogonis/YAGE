#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "btBulletDynamicsCommon.h"

class Transform
{
public:
	glm::vec3 position;
	glm::quat rotation;
	float scale;

	Transform();
	Transform(glm::vec3 position, float scale, glm::quat rotation);

	void SetScale(float scale);
	void SetPosition(const glm::vec3 &position);
	void SetRotation(float angle, glm::vec3 axis);
	void IncRotation(float angle, glm::vec3 axis);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	glm::mat4 getTranslationMatrix() const;
	glm::mat4 getScaleMatrix() const;
	glm::mat4 getRotationMatrix() const;
	glm::mat4 getTransformMatrix() const;

	Transform& Transform::operator=(const btTransform &trans);

	~Transform();
};