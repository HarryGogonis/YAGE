#pragma once
#include "Matrix4.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float, float, float, float);
	~Quaternion();
	float w, x, y, z;
	Matrix4 rotationMatrix();
	friend std::ostream& operator<<(std::ostream&, const Quaternion&);

};