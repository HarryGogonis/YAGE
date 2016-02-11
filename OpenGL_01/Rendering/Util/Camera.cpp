#include "Camera.h"


Camera Camera::GetInstance()
{
	if (!camInstance)
	{
		camInstance = new Camera();
	}
	return *camInstance;
}



Camera::Camera(Transform t)
{
	transform = t;
}


Camera::Camera()
{
	transform = Transform();
}


Camera::~Camera()
{
}
