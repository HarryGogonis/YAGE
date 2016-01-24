#include "Quaternion.h"

Quaternion::Quaternion()
{
	this->w = 0.0;
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
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
