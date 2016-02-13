#pragma once
#include "Transform.h"
#include "Matrix4.h"

class Camera
{
public:
	static Camera& GetInstance()
	{
		static Camera instance;

		return instance;
	}

	static Matrix4 Perspective();

	static Transform transform;
	static float fov;
	static float aspect;
	static float zNear;
	static float zFar;

	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;
private:
	Camera() {};
};

