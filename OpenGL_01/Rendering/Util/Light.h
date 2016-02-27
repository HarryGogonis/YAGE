#pragma once
#include "glm/vec3.hpp"
#include <GL\glew.h>
#include "../IGameObject.h"

class Light: public IGameObject
{
public:
	Light();
	~Light() {};

	void Create();
	void Create(GLuint program);
	virtual void Draw() override;
	virtual void Update() override;
	virtual void SetProgram(GLuint program) override;
	virtual void Destroy() override;

	virtual void SetTexture(const std::string&, GLuint) override;
	virtual const GLuint GetTexture(const std::string&) const override;

	glm::vec3 ambient; // light's contribution to ambient light
	glm::vec3 color;
	glm::vec3 position; // location of light if isLocal is true
	glm::vec3 halfVector; // direction of headlights for directional light ??
	glm::vec3 coneDirection; // spotlight cone direction
	float spotCosCutoff; // how wide the spotlight is [0-1]
	float spotExponent; // control light fall-off in the spotlight
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	void SetAttenuation(float constant, float linear, float quadratic);

protected:
	GLuint program;
	GLuint texture;
	unsigned int _id;

	bool isEnabled;
	int type; 

	// Holds shader locations
	struct LightUniformLocations
	{
		GLuint isEnabled, type,
				ambient, color, position,
				halfVector,
				coneDirection, spotCosCutoff, spotExponent,
				constantAttenuation, linearAttenuation, quadraticAttenuation;
	} ids;
private:
	static unsigned int count;

};

class DirectionalLight: public Light
{
public:
	DirectionalLight(glm::vec3 color, glm::vec3 position, glm::vec3 halfVector);

	virtual void Draw() override final;
};

class AmbientLight: public Light
{
public:
	AmbientLight(glm::vec3 color, float strength = 1.0);

	virtual void Draw() override final;
};

class PointLight : public Light
{
public:
	PointLight(glm::vec3 color, glm::vec3 position, 
		float constantAttenuation = 0.0f, float linearAttenuation = 1.0f, float quadraticAttenuation = 0.0f);

	virtual void Draw() override final;
};

class SpotLight : public Light
{
public:
	SpotLight(glm::vec3 color, glm::vec3 position, glm::vec3 coneDirection,
		float spotCosCutoff = 0.99f, float spotExponent = 0.0f,
		float constantAttenuation = 0.0f, float linearAttenuation = 1.0f, float quadraticAttenuation = 0.0f);

	virtual void Draw() override final;

};
