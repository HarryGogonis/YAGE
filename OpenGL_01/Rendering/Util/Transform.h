#pragma once
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix4.h"
class Transform
{
public:
	Vector4 position, scale;
	Quaternion rotation;

	Transform();
	Transform(Vector4 position, Vector4 scale, Quaternion rotation);
	Transform(Vector4 position);

	Matrix4 getScaleMatrix();
	Matrix4 getRotationMatrix();

	~Transform();
};