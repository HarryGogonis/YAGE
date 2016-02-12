#pragma once
#include "Vector4.h"
#define ROWS 4
#define COLS 4
class Matrix4
{
public:
	Matrix4();
	~Matrix4();
	static Matrix4 Identity();
	float& operator()(int, int);
	const float get(int, int) const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix4& v);

	Vector4 dot(Vector4);									  // Matrix*Vector dot product
	friend Matrix4 operator*(const Matrix4&, const Matrix4&); // Matrix*Matrix multiplication
	friend Matrix4 operator*(float, const Matrix4&);		  // Matrix*Scalar scaling
	friend Matrix4 operator+(const Matrix4&, const Matrix4&);
	friend Matrix4 operator-(const Matrix4&, const Matrix4&);
private:
	float m[ROWS][COLS];
};