#pragma once
#include <glm/glm.hpp>

/**********************************************************************************************//**
 * @class	Camera
 *
 * @brief	The game camera implemented as a Singleton.
 * 			Primary use is to generate Model-View-Projection matrices
 **************************************************************************************************/

class Camera
{
public:
	static Camera& GetInstance()
	{
		static Camera instance;

		return instance;
	}

	/**********************************************************************************************//**
	 * @fn	static glm::mat4 Camera::GetProjectionMatrix();
	 *
	 * @brief	Gets the camera projection matrix.
	 *
	 * @return	The projection matrix.
	 **************************************************************************************************/

	static glm::mat4 GetProjectionMatrix();

	/**********************************************************************************************//**
	 * @fn	static glm::mat4 Camera::GetViewMatrix();
	 *
	 * @brief	Gets the camera view matrix.
	 *
	 * @return	The view matrix.
	 **************************************************************************************************/

	static glm::mat4 GetViewMatrix();

	/**********************************************************************************************//**
	 * @fn	static glm::vec3 Camera::GetEyeDirection();
	 *
	 * @brief	Gets the direction the camera is looking at
	 *
	 * @return	The eye direction.
	 **************************************************************************************************/

	static glm::vec3 GetEyeDirection();
	static void resizeWindow(float width, float height);
	static void ComputeMatrices();

	/** @brief	The field of view */
	static float fov;
	/** @brief	The aspect ratio */
	static float aspect;
	static float zNear;
	static float zFar;

	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;

private:
	Camera();
	static float width;
	static float height;
};

