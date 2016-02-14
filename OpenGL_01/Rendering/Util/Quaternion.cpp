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
	double length = sqrt(x*x + y*y + z*z + w*w);
	this->w = w/length;
	this->x = x/length;
	this->y = y/length;
	this->z = z/length;
}

/*
	Depricated
*/
Quaternion::Quaternion(float x, float y, float z)
{
	this->w = 1.0;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::~Quaternion()
{
}

glm::mat4 Quaternion::rotationMatrix()
{
	
	glm::mat4 m = glm::mat4();
	m[0][0] = 1 - 2 * y * y - 2 * z * z;
	m[0][1] = 2 * x * y - 2 * w * z;
	m[0][2] = 2 * x * z + 2 * w * y;

	m[1][0] = 2 * x * y + 2 * w * z;
	m[1][1] = 1- 2 * x * x - 2 * z * z;
	m[1][2] = 2 * y * z - 2 * w * x;
	
	m[2][0] = 2 * x * z - 2 * w * y;
	m[2][1] = 2 * y * z + 2 * w * x;
	m[2][2] = 1 - 2 * x * x - 2 *  y * y;

	return m;
}

std::ostream & operator<<(std::ostream & os, const Quaternion & v)
{
	os << "w:" << v.w << "\tx:" << v.x << "\ty:" << v.y << "\tz:" << v.z << std::endl;
	return os;
}
