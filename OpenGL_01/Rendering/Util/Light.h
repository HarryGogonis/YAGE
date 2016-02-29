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
	virtual void Draw() override;
	virtual void Update() override;
	virtual void SetProgram(GLuint shaderName) override;
	virtual void Destroy() override;

	virtual void SetTexture(const std::string&, GLuint) override;
	virtual const GLuint GetTexture(const std::string&) const override;
protected:
	GLuint program;
	GLuint texture;
	unsigned int _id;

	bool isEnabled;
	int type; 

	glm::vec3 ambient; // light's contribution to ambient light
	glm::vec3 color;
	glm::vec3 position; // location of light if isLocal is true
	glm::vec3 halfVector; // direction of headlights for directional light
	glm::vec3 coneDirection; // spotlight cone
	glm::vec3 spotCosCutoff; // spotlight cosine cutoff
	glm::vec3 spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadradicAttenuation;

	struct UniformLocations
	{
		GLuint isEnabled, type,
				ambient, color, position,
				halfVector,
				coneDirection, spotCosCutoff, spotExponent,
				constantAttenuation, linearAttenuation, quadradicAttenuation;
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
