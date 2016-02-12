#include "Quaternion.h"

Quaternion::Quaternion()
{
	this->w = 1.0;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Quaternion::Quaternion(float w, float x, float y, float z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::~Quaternion()
{
}

Matrix4 Quaternion::rotationMatrix()
{
	Matrix4 m;
	m(0, 0) = w * w + x * x - y * y - z * z;
	m(0, 1) = 2 * x * y - 2 * w * z;
	m(0, 2) = 2 * x * z + 2 * w * y;

	m(1, 0) = 2 * x * y + 2 * w * z;
	m(1, 1) = w * w - x * x + y * y - z * z;
	m(1, 2) = 2 * y * z - 2 * w * x;
	
	m(2, 0) = 2 * x * z - 2 * w * y;
	m(2, 1) = 2 * y *z + 2 * w * x;
	m(2, 2) = w * w - x * x - y * y + z * z;

	return m;
}
