#pragma once
#include "Transform.h"

class Camera
{
public:
	static Camera GetInstance();
	~Camera();
	
	Transform transform;
private:
	Camera(Transform t);
	Camera();

	static Camera *camInstance;
};

