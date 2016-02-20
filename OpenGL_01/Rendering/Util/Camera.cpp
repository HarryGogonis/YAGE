#include "Camera.h"
#include <GL\freeglut.h>
#include <iostream>

float Camera::fov = 45.0f;
float Camera::aspect = 1.0f;

float hAngle = 3.14f;
float vAngle = 0.0f;
float speed = 100.0f;
float mouseSpeed = 0.5f;

glm::vec3 position = glm::vec3(0, 0, 5);
glm::vec3 direction, right, up;

float deltaTime = 0.0f;
int startTime = glutGet(GLUT_ELAPSED_TIME);
double x_origin, y_origin;
bool hRotationEnabled, vRotationEnabled;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 Camera::GetProjectionMatrix() {
	return ProjectionMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return ViewMatrix;
}

void updateMouseLocation(int x, int y)
{
	double dx = x - x_origin;
	double dy = y - y_origin;
	std::cout << "deltaTime" << deltaTime <<  std::endl;
	if (hRotationEnabled)
		hAngle += mouseSpeed * deltaTime * float(dx);
	if (vRotationEnabled)
		vAngle += mouseSpeed * deltaTime * float(dy);

	x_origin = x;
	y_origin = y;
}

/*
 * Callback for glutMouseFunc()
 * https://www.opengl.org/documentation/specs/glut/spec3/node50.html
*/
void onMouseButton(int button, int state, int x, int y)
{
	hRotationEnabled = false;
	vRotationEnabled = false;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_origin = x;
		y_origin = y;
		hRotationEnabled = true;
		vRotationEnabled = true;
	}
	else if (button == 3 && state == GLUT_DOWN) // Mouse wheel down
	{
		position += direction * speed * deltaTime;
	}
	else if (button == 4 && state == GLUT_DOWN) // Mouse wheel up
	{
		position -= direction * speed * deltaTime;
	}
}

void onKeyPressed(int key, int x, int y)
{

	std::cout << "deltaTime" << deltaTime << std::endl;
	if (key == GLUT_KEY_UP)
		position += up * speed * deltaTime;
	if (key == GLUT_KEY_DOWN)
		position -= up * speed * deltaTime;
	if (key == GLUT_KEY_RIGHT)
		position += right * speed * deltaTime;
	if (key == GLUT_KEY_LEFT)
		position -= right * speed * deltaTime;
}

//TODO switch from hardcoding in 1024/768, aspect, etc
void Camera::ComputeMatrices()
{
	int endTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = float(endTime - startTime)/1000.0f; // time elapsed in seconds

	// listen for mouse input
	//TODO call outside of this class
	glutMotionFunc(updateMouseLocation);

	direction = glm::vec3(
		cos(vAngle) * sin(hAngle),
		sin(vAngle),
		cos(vAngle) * cos(hAngle));

	right = glm::vec3(
		sin(hAngle - 3.14f/2.0f),
		0,
		cos(hAngle - 3.14/2.0f));

	up = cross(right, direction);

	// listen for mouse events
	//TODO call outside of this class
	glutSpecialFunc(onKeyPressed);
	glutMouseFunc(onMouseButton);

	ProjectionMatrix = glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
	ViewMatrix = lookAt(
			position, // camera position
			position + direction, // camera looks here
			up
		);
	startTime = endTime; // update "previous" time

}

