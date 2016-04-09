#include "Camera.h"
#include <GL\freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <algorithm>

float Camera::fov = 45.0f;
float Camera::aspect;
float Camera::width;
float Camera::height;

float speed = 50.0f;
float mouseSpeed = 1.0f;

glm::mat4 viewMatrix;
glm::mat4 projMatrix;

glm::vec3 eyeVector = glm::vec3(0, 0, 15);
float pitch, yaw = 0.0f;

float deltaTime = 0.0f;
int startTime = glutGet(GLUT_ELAPSED_TIME);

double x_origin, y_origin;

bool leftMouseDown;

glm::mat4 Camera::GetProjectionMatrix()
{
	return projMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

glm::vec3 Camera::GetEyeDirection()
{
	return eyeVector;
}

void Camera::resizeWindow(float width, float height)
{
	Camera::width = width;
	Camera::height = height;
	Camera::aspect = width / height;
}

void updateMouseLocation(int x, int y)
{
	double dx = x - x_origin;
	double dy = y - y_origin;

	if (leftMouseDown)
	{
		yaw += mouseSpeed * dx * deltaTime;
		pitch += mouseSpeed * dy * deltaTime;
	}

	x_origin = x;
	y_origin = y;
}

/*
 * Callback for glutMouseFunc()
 * https://www.opengl.org/documentation/specs/glut/spec3/node50.html
*/
void onMouseButton(int button, int state, int x, int y)
{
	leftMouseDown = false;
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_origin = x;
		y_origin = y;
		leftMouseDown = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		x_origin = x;
		y_origin = y;
	}
	else if (button == 3 && state == GLUT_DOWN) // Mouse wheel down
	{
		// Zoom out
		Camera::fov = std::max(Camera::fov - 20.0 * speed * deltaTime, static_cast<double>(10));

	}
	else if (button == 4 && state == GLUT_DOWN) // Mouse wheel up
	{
		// Zoom in
		Camera::fov = std::min(Camera::fov + 20.0 * speed * deltaTime, static_cast<double>(120));
	}
}

void onKeyPressed(const unsigned char key, int x, int y)
{
	float dx = 0;
	float dz = 0; 
	float dy = 0; 

	switch (key)
	{
	case 'w':
	{
		dz = 2;
		break;
	}
	case 's':
	{
		dz = -2;
		break;
	}
	case 'a':
	{
		dx = -2;
		break;
	}
	case 'd':
	{
		dx = 2;
		break;
	}
	case 'e':
	{
		dy = 2;
		break;
	}
	case 'q':
	{
		dy = -2;
		break;
	}
	default:
		break;
	}

	glm::mat4 mat = viewMatrix;
	glm::vec3 right(mat[0][0], mat[1][0], mat[2][0]);
	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 up(mat[0][1], mat[1][1], mat[2][1]);

	eyeVector += (-dz * forward + dx * right + dy * up) * speed * deltaTime;
}



//TODO switch from hardcoding in 1024/768, aspect, etc
void Camera::ComputeMatrices()
{
	int endTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = float(endTime - startTime)/1000.0f; // time elapsed in seconds

	// listen for mouse input
	//TODO call outside of this class
	glutMotionFunc(updateMouseLocation);

	// Build rotation matrix
	glm::quat matPitch = glm::quat();
	glm::quat matYaw = glm::quat();
	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0, 0));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotate = glm::mat4_cast(matPitch * matYaw);
	
	// Build translation matrix
	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, -eyeVector);

	// listen for mouse events
	//TODO call outside of this class
	glutKeyboardFunc(onKeyPressed);
	glutMouseFunc(onMouseButton);

	projMatrix = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);

	viewMatrix = rotate * translate;
	startTime = endTime; // update "previous" time
}

Camera::Camera()
{
}
