#pragma once
#include "Matrix3.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float, float, float, float);
	~Quaternion();
	float w, x, y, z;
	Matrix3 rotationMatrix();

};