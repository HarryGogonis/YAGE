#include "Camera.h"

float Camera::fov = 90.0f;
float Camera::aspect = 1.0f;
float Camera::zNear = 1.0f;
float Camera::zFar = 50.0f;
Transform Camera::transform = Transform(
	Vector4(0.0, 0.0, 0.0, 0.0),
	Vector4(0.0, 0.0, 0.0, 0.0),
	Quaternion(1.0, 0.5, 0.5, 0.5)
	);

Matrix4 Camera::Perspective() {
	float D2R = 3.1415927f / 180.0f;
	float yScale = 1.0f / tan(D2R * fov / 2.0f);
	float xScale = yScale / aspect;
	float delta = zNear - zFar;

	Matrix4 m = Matrix4::Identity();
	m(0, 0) = xScale;
	m(1, 1) = yScale;
	m(2, 2) = (zFar + zNear) / delta;
	m(2, 3) = -1.0f;
	m(3, 2) = zFar*zNear / delta;

	//TODO add m
	return  -1 * transform.getRotationMatrix() * transform.getTranslationMatrix();
}
