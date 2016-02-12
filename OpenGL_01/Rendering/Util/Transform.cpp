#include "Transform.h"

Transform::Transform()
{
	this->position = Vector4();
	this->scale = Vector4(1.0, 1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

Transform::Transform(Vector4 position, Vector4 scale, Quaternion rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Transform::Transform(Vector4 position)
{
	this->position = position;
	this->scale = Vector4(1.0, 1.0, 1.0, 1.0);
	this->rotation = Quaternion();
}

Matrix4 Transform::getScaleMatrix()
{
	Matrix4 m = Matrix4::Zeroes();
	m(0, 0) = scale.x;
	m(1, 1) = scale.y;
	m(2, 2) = scale.z;
	return m;
}

Matrix4 Transform::getRotationMatrix()
{
	return rotation.rotationMatrix();
}

Transform::~Transform()
{

}
