#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const glm::vec3 &vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

Vector3::~Vector3()
{
}

void Vector3::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

std::ostream & operator<<(std::ostream & os, const Vector3 & v)
{
	os << "x:" << v.x << "\ty:" << v.x << "\tz:" << v.z << std::endl;
	return os;
}
