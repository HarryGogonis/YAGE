#include "Transform.h"

Transform::Transform()
{
	this->position = Vector3();
	this->scale = Vector3(1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

Transform::Transform(Vector3 position, Vector3 scale, Quaternion rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Transform::Transform(Vector3 position)
{
	this->position = position;
	this->scale = Vector3(1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

Matrix3 Transform::getScaleMatrix()
{
	Matrix3 m = Matrix3::Zeroes();
	m(0, 0) = scale.x;
	m(1, 1) = scale.y;
	m(2, 2) = scale.z;
	return m;
}

Matrix3 Transform::getRotationMatrix()
{
	return rotation.rotationMatrix();
}

Transform::~Transform()
{

}
