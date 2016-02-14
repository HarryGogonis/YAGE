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
	glm::mat4 rotationMatrix();
	friend std::ostream& operator<<(std::ostream&, const Quaternion&);

	void setX(float);
	void setY(float);
	void setZ(float);
	void setW(float);
	void set(float, float, float, float);

	float getX();
	float getY();
	float getZ();
	float getW();

private:
	float w, x, y, z;

};
