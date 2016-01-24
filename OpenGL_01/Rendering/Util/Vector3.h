#pragma once
#include <string>
#include <iostream>
#include <glm\vec3.hpp>

/* Ref: http://docs.unity3d.com/ScriptReference/Vector3.html */
class Vector3
{
public:
	Vector3();
	Vector3(float, float, float);
	Vector3(const glm::vec3&);
	~Vector3();
	void Set(float, float, float);
	float x, z, y;

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};