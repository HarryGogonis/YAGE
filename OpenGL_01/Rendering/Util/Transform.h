#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix3.h"
class Transform
{
public:
	Vector3 position, scale;
	Quaternion rotation;

	Transform();
	Transform(Vector3 position, Vector3 scale, Quaternion rotation);
	Transform(Vector3 position);

	Matrix3 getScaleMatrix();
	Matrix3 getRotationMatrix();

	~Transform();
};