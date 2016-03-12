#include "Transform.h"

Transform::Transform()
{
	this->position = glm::vec4(0.0, 0.0, 0.0, 1.0);
	this->scale = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

void Transform::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
}

void Transform::SetPosition(const glm::vec3& position)
{
	this->position = position;
}

void Transform::SetRotation(float angle, glm::vec3 axis)
{
	glm::mat4 m = glm::mat4(1.0f);
	m[0][3] = position.x;
	m[1][3] = position.y;
	m[2][3] = position.z;
	return m;
}

// Rotate along X Axis - Angle is in degrees
void Transform::RotateX(float angle)
{
	glm::mat4 m = glm::mat4(1.0f);
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
	return m;
}

glm::mat4 Transform::getRotationMatrix()
{
	return rotation.rotationMatrix();
}

Transform::~Transform()
{

}
