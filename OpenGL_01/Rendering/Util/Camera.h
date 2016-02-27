#pragma once
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	static Camera& GetInstance()
	{
		static Camera instance;

		return instance;
	}

	static glm::mat4 GetProjectionMatrix();
	static glm::mat4 GetViewMatrix();
	static glm::vec3 GetEyeDirection();
	static void ComputeMatrices();

	static float fov;
	static float aspect;
	static float zNear;
	static float zFar;
	//static Transform transform;

	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;

private:
	Camera();
	//static glm::mat4 viewMatrix;
	//static glm::mat4 projMatrix;
};

