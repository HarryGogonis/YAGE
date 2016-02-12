#pragma once
#include "Vector4.h"
#define ROWS 4
#define COLS 4
class Matrix4
{
public:
	Matrix4();
	~Matrix4();
	static Matrix4 Zeroes();
	Vector4 dot(Vector4);
	float& operator()(int, int);
	const float get(int, int) const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix4& v);
private:
	float m[ROWS][COLS];
};