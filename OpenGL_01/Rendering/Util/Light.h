#pragma once
#include "glm/vec3.hpp"
#include <GL\glew.h>
#include "../IGameObject.h"

/**********************************************************************************************//**
 * @class	Light
 *
 * @brief	A light is a special class of Game Object that mostly just sends uniform data to the shaders.
 * 			Lights are fundamental to the shading pipeline! Without a light, nothing will show up in the scene.
 **************************************************************************************************/

class Light: public IGameObject
{
public:
	Light();
	~Light() {};

	/**********************************************************************************************//**
	 * @fn	void Light::Draw(GLuint program)
	 *
	 * @brief	Sets up the light uniform location id's from the program.
	 * 			Each subclass must then send their corresponding params to the shader
	 *
	 * @param	program	The shader program.
	 **************************************************************************************************/

	virtual void Draw(GLuint) override;

	/**********************************************************************************************//**
	 * @fn	virtual void Light::DrawShadow(GLuint) override;
	 *
	 * @brief	Sends shadow information. Each subclass must implement this functionality!
	 *
	 *
	 * @param	program The shader program.
	 **************************************************************************************************/

	virtual void DrawShadow(GLuint) override;

	/**********************************************************************************************//**
	 * @fn	virtual void Light::Update() override;
	 *
	 * @brief	Updates the light. This currently does nothing! Draw() does update the light.
	 **************************************************************************************************/

	virtual void Update() override;

	/**********************************************************************************************//**
	 * @fn	virtual void Light::Destroy() override;
	 *
	 * @brief	Destroys the light. This currently only turns off the enabled flag!
	 **************************************************************************************************/

	virtual void Destroy() override;

	virtual void SetTexture(const std::string&, const TextureType&, const GLuint&) override;
	virtual const GLuint GetTexture(const std::string&) const override;

	/**********************************************************************************************//**
	 * @fn	bool Light::EnableShadows();
	 *
	 * @brief	Enables shadow generation for this light
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool EnableShadows();

	/**********************************************************************************************//**
	 * @fn	bool Light::DisableShadows();
	 *
	 * @brief	Disables shadow generation for this light.
	 *
	 * @return	true if it succeeds, false if it fails.
	 **************************************************************************************************/

	bool DisableShadows();

	/** @brief	light's contribution to ambient light. */
	glm::vec3 ambient;
	/** @brief	The color/intensity of the light */
	glm::vec3 color;
	/** @brief	location of light if isLocal is true. For directional light, it is the direction */
	glm::vec3 position;
	/** @brief	?? direction of headlights for directional light ?? */
	glm::vec3 halfVector;
	/** @brief	spotlight cone direction. */
	glm::vec3 coneDirection;
	/** @brief	how wide the spotlight is [0-1]. */
	float spotCosCutoff;
	/** @brief	control light fall-off in the spotlight. */
	float spotExponent;
	/** @brief	constant light fall-out */
	float constantAttenuation;
	/** @brief	linear light fall-off  */
	float linearAttenuation;
	/** @brief	quadratic light fall-out */
	float quadraticAttenuation;

	/**********************************************************************************************//**
	 * @fn	void Light::SetAttenuation(float constant = 0.0f, float linear = 1.0f, float quadratic = 0.0f);
	 *
	 * @brief	Sets the attenutation parameters.
	 * 			See this wiki article for more information about attenuation:
	 * 			https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff
	 *
	 * @author	Harry
	 * @date	4/14/2016
	 *
	 * @param	constant 	The constant attenuation factor.
	 * @param	linear   	The linear attenuation factor.
	 * @param	quadratic	The quadratic attenuation factor.
	 **************************************************************************************************/

	void SetAttenuation(float constant = 0.0f, float linear = 1.0f, float quadratic = 0.0f);

	/** @brief	true if this object is enabled. */
	bool isEnabled;

protected:
	GLuint texture;
	unsigned int _id;
	bool castsShadow;
	int type; 


	/**********************************************************************************************//**
	 * @struct	LightUniformLocations
	 *
	 * @brief	Holds the various uniform location ID's of the Light
	 **************************************************************************************************/

	struct LightUniformLocations
	{
		GLuint isEnabled, 
				type,
				ambient, 
				color, 
				position,
				halfVector,
				coneDirection, 
				spotCosCutoff, 
				spotExponent,
				constantAttenuation, 
				linearAttenuation, 
				quadraticAttenuation;
	} ids;
private:
	/** @brief	Number of Light instances. */
	static unsigned int count;
};

/**********************************************************************************************//**
 * @class	DirectionalLight
 *
 * @brief	A directional light. Comes from "infinity" and lights up anything in the direction it is coming from
 **************************************************************************************************/

class DirectionalLight: public Light
{
public:
	DirectionalLight(glm::vec3 color, glm::vec3 position, glm::vec3 halfVector);

	virtual void Draw(GLuint) override final;
	virtual void DrawShadow(GLuint) override  final;
};

/**********************************************************************************************//**
 * @class	AmbientLight
 *
 * @brief	An ambient light. Uniformly lights up everything.
 **************************************************************************************************/

class AmbientLight: public Light
{
public:
	AmbientLight(glm::vec3 color, float strength = 1.0);

	virtual void Draw(GLuint) override final;
};

/**********************************************************************************************//**
 * @class	PointLight
 *
 * @brief	A point light.
 **************************************************************************************************/

class PointLight : public Light
{
public:
	PointLight(glm::vec3 color, glm::vec3 position, 
		float constantAttenuation = 0.0f, float linearAttenuation = 1.0f, float quadraticAttenuation = 0.0f);

	virtual void Draw(GLuint) override final;
};

/**********************************************************************************************//**
 * @class	SpotLight
 *
 * @brief	A spot light.
 **************************************************************************************************/

class SpotLight : public Light
{
public:
	SpotLight(glm::vec3 color, glm::vec3 position, glm::vec3 coneDirection,
		float spotCosCutoff = 0.99f, float spotExponent = 0.0f,
		float constantAttenuation = 0.0f, float linearAttenuation = 1.0f, float quadraticAttenuation = 0.0f);

	virtual void Draw(GLuint) override final;

};
