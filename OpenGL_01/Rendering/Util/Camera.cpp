#include "Camera.h"
#include <GL\freeglut.h>
#include <iostream>

float Camera::fov = 45.0f;
float Camera::aspect = 1.0f;

float hAngle = 3.14f;
float vAngle = 0.0f;
float speed = 3.0f;
float mouseSpeed = 0.005f;

glm::vec3 position = glm::vec3(0, 0, 5);
glm::vec3 direction, right, up;

float deltaTime = 0.0f;
double cursor_x, cursor_y;
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
	cursor_x = x;
	cursor_y = y;
}

void keyPressed(int key, int x, int y)
{
	std::cout << "KEY PRESSED: " << key << std::endl;
	if (key == GLUT_KEY_UP)
		position += direction * deltaTime * speed;
	if (key == GLUT_KEY_DOWN)
		position -= direction * deltaTime * speed;
	if (key == GLUT_KEY_RIGHT)
		position += right * deltaTime * speed;
	if (key == GLUT_KEY_LEFT)
		position -= right * deltaTime * speed;
}

//TODO switch from hardcoding in 1024/768, aspect, etc
void Camera::ComputeMatrices()
{
	static int pTime = glutGet(GLUT_ELAPSED_TIME); // called once
	int cTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = float(cTime - pTime)/1000.0f; // time elapsed in seconds

	// listen for mouse input
	glutPassiveMotionFunc(updateMouseLocation);
	// reset mouse position
	glutWarpPointer(1024 / 2, 768 / 2);

	hAngle += mouseSpeed * float(1024 / 2 - cursor_x);
	vAngle += mouseSpeed * float(768 / 2 - cursor_y);

	direction = glm::vec3(
		cos(vAngle) * sin(hAngle),
		sin(vAngle),
		cos(vAngle) * cos(hAngle));

	right = glm::vec3(
		sin(hAngle - 3.14f/2.0f),
		0,
		cos(hAngle - 3.14/2.0f));

	up = glm::cross(right, direction);

	// listen for UP/DOWN/RIGHT/LEFT
	glutSpecialFunc(keyPressed);

	ProjectionMatrix = glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(
			position, // camera position
			position + direction, // camera looks here
			up
		);
	pTime = cTime; // update "previous" time

}

