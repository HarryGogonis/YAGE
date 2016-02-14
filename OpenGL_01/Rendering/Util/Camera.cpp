#include "Camera.h"
#include <GL\freeglut.h>
#include <iostream>

float Camera::fov = 45.0f;
float Camera::aspect = 1.0f;

float hAngle = 3.14f;
float vAngle = 0.0f;
float speed = 3.0f;
float mouseSpeed = 0.05f;

glm::vec3 position = glm::vec3(4, 3, 3);
glm::vec3 direction, right, up;

float deltaTime = 0.0f;
double cursor_x, cursor_y;
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
	std::cout << "x=" << x << "y=" << y << std::endl;
	if (hRotationEnabled)
		hAngle += mouseSpeed * deltaTime * float(1024 / 2 - cursor_x);
	if (vRotationEnabled)
		vAngle += mouseSpeed * deltaTime * float(768 / 2 - cursor_y);
}

/*
 * Callback for glutMouseFunc()
 * https://www.opengl.org/documentation/specs/glut/spec3/node50.html
*/
void onMouseButton(int button, int state, int x, int y)
{
	std::cout << "button: " << button << "\tstate: " << state << std::endl;
	hRotationEnabled = false;
	vRotationEnabled = false;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		hRotationEnabled = true;
		vRotationEnabled = true;
	}
}

void onKeyPressed(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		position += direction * speed;
	if (key == GLUT_KEY_DOWN)
		position -= direction * speed;
	if (key == GLUT_KEY_RIGHT)
		position += right * speed;
	if (key == GLUT_KEY_LEFT)
		position -= right * speed;
}

//TODO switch from hardcoding in 1024/768, aspect, etc
void Camera::ComputeMatrices()
{
	static int pTime = glutGet(GLUT_ELAPSED_TIME); // called once. Wrong! TODO: Fix
	int cTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = float(cTime - pTime)/1000.0f; // time elapsed in seconds

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

	up = glm::cross(right, direction);

	// listen for mouse events
	//TODO call outside of this class
	glutSpecialFunc(onKeyPressed);
	glutMouseFunc(onMouseButton);

	ProjectionMatrix = glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(
			position, // camera position
			direction, // camera looks here
			up
		);
	pTime = cTime; // update "previous" time

}

