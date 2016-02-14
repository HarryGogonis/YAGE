#include "Transform.h"

Transform::Transform()
{
	this->position = glm::vec4();
	this->scale = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

Transform::Transform(glm::vec4 position, glm::vec4 scale, Quaternion rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Transform::Transform(glm::vec4 position)
{
	this->position = position;
	this->scale = glm::vec4(1.0, 1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

glm::mat4 Transform::getTranslationMatrix()
{
	glm::mat4 m = glm::mat4();
	m[0][3] = position.x;
	m[1][3] = position.y;
	m[2][3] = position.z;
	return m;
}

glm::mat4 Transform::getScaleMatrix()
{
	glm::mat4 m = glm::mat4();
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
