#include "Transform.h"
#include <glm/gtx/transform.hpp>

Transform::Transform()
{
	this->position = glm::vec3(0.0, 0.0, 0.0);
	this->scale = 1.f;
	this->rotation = glm::quat();
}

Transform::Transform(glm::vec3 position, float scale, glm::quat rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

void Transform::SetScale(float scale)
{
	this->scale = scale;
}

void Transform::SetPosition(const glm::vec3& position)
{
	this->position = position;
}

void Transform::SetRotation(float angle, glm::vec3 axis)
{
	this->rotation = glm::angleAxis(angle, axis);
}

void Transform::IncRotation(float angle, glm::vec3 axis)
{
	this->rotation *= glm::angleAxis(angle, axis);
}

// Rotate along X Axis - Angle is in degrees
void Transform::RotateX(float angle)
{
	this->IncRotation(glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
}

void Transform::RotateY(float angle)
{
	this->IncRotation(glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
}

void Transform::RotateZ(float angle)
{
	this->IncRotation(glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
}

glm::mat4 Transform::getTranslationMatrix() const
{
	return glm::translate(glm::mat4(1.0f), this->position);
}

glm::mat4 Transform::getScaleMatrix() const
{
	return glm::scale(glm::mat4(1.0f), glm::vec3(this->scale));
}

glm::mat4 Transform::getRotationMatrix() const
{
	return glm::mat4_cast(rotation);
}

glm::mat4 Transform::getTransformMatrix() const
{
	//return getTranslationMatrix() * getScaleMatrix() * getRotationMatrix();//
	return getTranslationMatrix() *
		getRotationMatrix() *
		getScaleMatrix();
}

Transform& Transform::operator=(const btTransform &trans)
{
	btQuaternion quat = trans.getRotation();
	btVector3 pos = trans.getOrigin();
	rotation.x = quat.getX();
	rotation.y = quat.getY();
	rotation.z = quat.getZ();
	rotation.w = quat.getW();
	position.x = pos.getX();
	position.y = pos.getY();
	position.z = pos.getZ();
	return *this;
}

Transform::~Transform()
{

}
