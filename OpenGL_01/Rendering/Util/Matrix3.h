#pragma once
#include "Vector3.h"
#define ROWS 3
#define COLS 3
class Matrix3
{
public:
	Matrix3();
	~Matrix3();
	static Matrix3 Zeroes();
	Vector3 dot(Vector3);
	float& operator()(int, int);
	const float get(int, int) const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix3& v);
private:
	float m[3][3];
};