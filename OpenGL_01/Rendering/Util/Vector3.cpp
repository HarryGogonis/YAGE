#include "Vector3.h"

const float Vector3::SCALE = 0.01f;

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

const glm::vec3 Vector3::toVec3() const
{
	return Vector3::SCALE * glm::vec3(x,y,z);
}

Vector3 operator*(Vector3 v1, Vector3 v2)
{
	//TODO implement vector multiplication
	return Vector3(v1.toVec3() * v2.toVec3());
}

Vector3 operator+(Vector3 v1, Vector3 v2)
{
	return Vector3(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z);
}

Vector3 operator*(float c, Vector3 v)
{
	return Vector3(c * v.x, c * v.y, c * v.z);
}

bool operator==(Vector3 v1, Vector3 v2)
{
	return (v1.x == v2.x) &&
		(v1.y == v2.y) &&
		(v1.z == v2.z);
}

std::ostream & operator<<(std::ostream & os, const Vector3 & v)
{
	os << "x:" << v.x << "\ty:" << v.y << "\tz:" << v.z << std::endl;
	return os;
}
