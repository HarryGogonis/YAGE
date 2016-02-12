#pragma once
#include <string>
#include <iostream>
#include <glm\vec4.hpp>
/* Ref: http://docs.unity3d.com/ScriptReference/Vector4.html */
class Vector4
{
public:
	static const float SCALE; // [0,100] => [0,1]

	Vector4();
	Vector4(float, float, float, float);
	Vector4(float, float, float);
	Vector4(const glm::vec4&);
	~Vector4();
	
	float& operator[](int);
	const glm::vec4 toVec4() const;

	float w, x, z, y;

	friend Vector4 operator* (Vector4, Vector4);
	friend Vector4 operator+ (Vector4, Vector4);
	friend Vector4 operator* (float, Vector4);
	friend bool operator== (Vector4, Vector4);
	
	friend std::ostream& operator<<(std::ostream& os, const Vector4& v);
};