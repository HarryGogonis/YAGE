#pragma once
#include <string>
#include <iostream>
#include <glm\vec3.hpp>

/* Ref: http://docs.unity3d.com/ScriptReference/Vector3.html */
class Vector3
{
public:
	static const float SCALE; // [0,100] => [0,1]

	Vector3();
	Vector3(float, float, float);
	Vector3(const glm::vec3&);
	~Vector3();
	void Set(float, float, float);

	const glm::vec3 toVec3() const;

	float x, z, y;

	friend Vector3 operator* (Vector3, Vector3);
	friend Vector3 operator+ (Vector3, Vector3);
	friend Vector3 operator* (float, Vector3);
	friend bool operator== (Vector3, Vector3);

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};