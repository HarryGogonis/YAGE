#include "Matrix4.h"

Matrix4::Matrix4()
{
}

Matrix4::~Matrix4()
{
}

Matrix4 Matrix4::Zeroes()
{
	Matrix4 m;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			m(i,j) = 0;
		}
	}
	return m;
}

float & Matrix4::operator()(int row, int col)
{
	assert(col >= 0 && col < COLS);
	assert(row >= 0 && row < ROWS);
	return m[row][col];
}

const float Matrix4::get(int row, int col) const
{
	assert(col >= 0 && col < COLS);
	assert(row >= 0 && row < ROWS);
	return m[row][col];
}

Vector4 Matrix4::dot(Vector4 v)
{
	return Vector4(
		m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
		m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
		m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
		m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
		);
}

std::ostream & operator<<(std::ostream & os, const Matrix4 & m)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			os << m.get(i, j) << "\t";
		}
		os << std::endl;
	}
	return os;
	// TODO: insert return statement here
}
