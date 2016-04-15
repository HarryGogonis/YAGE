#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "btBulletDynamicsCommon.h"

/**********************************************************************************************//**
 * @class	Transform
 *
 * @brief	Transform composed of Scale, Rotation (as a quaternion), and Translation.
 * 			Transformation is applied in the order: Scale -> Rotate -> Translate
 **************************************************************************************************/

class Transform
{
public:
	glm::vec3 position;
	glm::quat rotation;
	float scale;

	Transform();
	Transform(glm::vec3 position, float scale, glm::quat rotation);

	/**********************************************************************************************//**
	 * @fn	void Transform::SetScale(float scale);
	 *
	 * @brief	Sets a scale.
	 *
	 * @param	scale	The scale.
	 **************************************************************************************************/

	void SetScale(float scale);

	/**********************************************************************************************//**
	 * @fn	void Transform::SetPosition(const glm::vec3 &position);
	 *
	 * @brief	Sets a position.
	 *
	 * @param	position	The position.
	 **************************************************************************************************/

	void SetPosition(const glm::vec3 &position);

	/**********************************************************************************************//**
	 * @fn	void Transform::SetRotation(float angle, glm::vec3 axis);
	 *
	 * @brief	Sets a rotation.
	 *
	 * @param	angle	The angle in degrees.
	 * @param	axis 	The axis.
	 **************************************************************************************************/

	void SetRotation(float angle, glm::vec3 axis);

	/**********************************************************************************************//**
	 * @fn	void Transform::IncRotation(float angle, glm::vec3 axis);
	 *
	 * @brief	Increment rotation.
	 *
	 * @param	angle	The angle in degrees.
	 * @param	axis 	The axis.
	 **************************************************************************************************/

	void IncRotation(float angle, glm::vec3 axis);

	/**********************************************************************************************//**
	 * @fn	void Transform::RotateX(float angle);
	 *
	 * @brief	Rotate along x axis.
	 *
	 * @param	angle	The angle in degrees.
	 **************************************************************************************************/

	void RotateX(float angle);

	/**********************************************************************************************//**
	 * @fn	void Transform::RotateY(float angle);
	 *
	 * @brief	Rotate along y axis.
	 *
	 * @param	angle	The angle in degrees.
	 **************************************************************************************************/

	void RotateY(float angle);

	/**********************************************************************************************//**
	 * @fn	void Transform::RotateZ(float angle);
	 *
	 * @brief	Rotate along z axis.
	 *
	 * @param	angle	The angle in degrees.
	 **************************************************************************************************/

	void RotateZ(float angle);

	/**********************************************************************************************//**
	 * @fn	glm::mat4 Transform::getTranslationMatrix() const;
	 *
	 * @brief	Gets translation matrix.
	 *
	 * @return	The translation matrix.
	 **************************************************************************************************/

	glm::mat4 getTranslationMatrix() const;

	/**********************************************************************************************//**
	 * @fn	glm::mat4 Transform::getScaleMatrix() const;
	 *
	 * @brief	Gets scale matrix.
	 *
	 * @return	The scale matrix.
	 **************************************************************************************************/

	glm::mat4 getScaleMatrix() const;

	/**********************************************************************************************//**
	 * @fn	glm::mat4 Transform::getRotationMatrix() const;
	 *
	 * @brief	Gets rotation matrix.
	 *
	 * @return	The rotation matrix.
	 **************************************************************************************************/

	glm::mat4 getRotationMatrix() const;

	/**********************************************************************************************//**
	 * @fn	glm::mat4 Transform::getTransformMatrix() const;
	 *
	 * @brief	Gets transformation matrix.
	 * 			Transformation applied in the order: Scale -> Rotate -> Translate
	 *
	 * @return	The transform matrix.
	 **************************************************************************************************/

	glm::mat4 getTransformMatrix() const;

	/**********************************************************************************************//**
	 * @fn	Transform& Transform::operator=(const btTransform &trans);
	 *
	 * @brief	Assignment operator.
	 *
	 * @param	trans	The transform from ASSIMP
	 *
	 * @return	A shallow copy of this object.
	 **************************************************************************************************/

	Transform& Transform::operator=(const btTransform &trans);

	~Transform();
};