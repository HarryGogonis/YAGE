#include "Vector4.h"

const float Vector4::SCALE = 0.01f;

Vector4::Vector4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
}

Vector4::Vector4(float x, float y, float z)
{
	this->w = 1.0f;
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector4::Vector4(const glm::vec4 &vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
}

Vector4::~Vector4()
{
}

float & Vector4::operator[](int n)
{
	assert(n >= 0 && n < 4);
	if (n == 0) return x;
	if (n == 1) return y;
	if (n == 2) return z;
	return w;
}

const glm::vec4 Vector4::toVec4() const
{
	return Vector4::SCALE * glm::vec4(x,y,z,w);
}

Vector4 operator*(Vector4 v1, Vector4 v2)
{
	//TODO implement vector multiplication
	return Vector4(v1.toVec4() * v2.toVec4());
}

Vector4 operator+(Vector4 v1, Vector4 v2)
{
	return Vector4(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z,
		v1.w + v2.w);
}

Vector4 operator-(Vector4 A, Vector4 B)
{
	return A + (-1.0f) * B;
}

Vector4 operator*(float c, Vector4 v)
{
	return Vector4(c * v.x, c * v.y, c * v.z, c * v.w);
}

bool operator==(Vector4 v1, Vector4 v2)
{
	return (v1.x == v2.x) &&
		(v1.y == v2.y) &&
		(v1.z == v2.z) &&
		(v1.w == v2.w);
}

std::ostream & operator<<(std::ostream & os, const Vector4 & v)
{
	os << "w:" << v.w << "\tx:" << v.x << "\ty:" << v.y << "\tz:" << v.z << std::endl;
	return os;
}
