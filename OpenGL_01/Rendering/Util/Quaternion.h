#pragma once
#include <glm/glm.hpp>
#include <iostream>

class Quaternion
{
public:
	Quaternion();
	Quaternion(float, float, float, float);
	Quaternion(float, float, float);
	~Quaternion();
	float w, x, y, z;
	glm::mat4 rotationMatrix();
	friend std::ostream& operator<<(std::ostream&, const Quaternion&);

};
