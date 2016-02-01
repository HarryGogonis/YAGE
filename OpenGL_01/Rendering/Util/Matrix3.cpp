#include "Matrix3.h"

Matrix3::Matrix3()
{
}

Matrix3::~Matrix3()
{
}

Matrix3 Matrix3::Zeroes()
{
	Matrix3 m;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			m(i,j) = 0;
		}
	}
	return m;
}

float & Matrix3::operator()(int row, int col)
{
	assert(col >= 0 && col < 3);
	assert(row >= 0 && row < 3);
	return m[row][col];
}

const float Matrix3::get(int row, int col) const
{
	assert(col >= 0 && col < 3);
	assert(row >= 0 && row < 3);
	return m[row][col];
}

Vector3 Matrix3::dot(Vector3 v)
{
	return Vector3(
		m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
		m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
		m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]
		);
}

std::ostream & operator<<(std::ostream & os, const Matrix3 & m)
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
