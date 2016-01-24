#pragma once

class Quaternion
{
public:
	Quaternion();
	Quaternion(float, float, float, float);
	~Quaternion();
	float w, x, y, z;

};