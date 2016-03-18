#include "Light.h"
#include <string>

const static int AMBIENT_LIGHT = 0;
const static int DIRECTIONAL_LIGHT = 1;
const static int POINT_LIGHT = 2;
const static int SPOT_LIGHT = 3;

unsigned int Light::count = 0;

Light::Light()
{
	this->isEnabled = true;
	this->_id = count++;
}

void Light::Draw(GLuint program)
{
	const std::string prefix = "Lights[" + std::to_string(_id) + "].";
	ids.isEnabled = glGetUniformLocation(program, (prefix + "isEnabled").c_str());
	ids.type = glGetUniformLocation(program, (prefix + "type").c_str());
	ids.ambient = glGetUniformLocation(program, (prefix + "ambient").c_str());
	ids.color = glGetUniformLocation(program, (prefix + "color").c_str());
	ids.position = glGetUniformLocation(program, (prefix + "position").c_str());
	ids.halfVector = glGetUniformLocation(program, (prefix + "halfVector").c_str());
	ids.coneDirection = glGetUniformLocation(program, (prefix + "coneDirection").c_str());
	ids.spotCosCutoff = glGetUniformLocation(program, (prefix + "spotCosCutoff").c_str());
	ids.spotExponent = glGetUniformLocation(program, (prefix + "spotExponent").c_str());
	ids.constantAttenuation = glGetUniformLocation(program, (prefix + "constantAttenuation").c_str());
	ids.linearAttenuation = glGetUniformLocation(program, (prefix + "linearAttenuation").c_str());
	ids.quadraticAttenuation = glGetUniformLocation(program, (prefix + "quadradicAttenuation").c_str());
}

void Light::Update()
{
	// override
}

void Light::SetProgram(GLuint program)
{
	this->program = program;
}

void Light::Destroy()
{
	//TODO what happens when a light is destroyed?
	this->isEnabled = false;
}

void Light::SetTexture(const std::string&, const TextureType&, const GLuint&)
{
	//TODO support textures on lights? probably not!
	throw "Textures not supported with Lights";
}

const GLuint Light::GetTexture(const std::string&) const
{
	throw "Textures not supported with Lights";
}

void Light::SetAttenuation(float constant, float linear, float quadratic)
{
	this->constantAttenuation = constant;
	this->linearAttenuation = linear;
	this->quadraticAttenuation = quadratic;
}

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction, glm::vec3 halfVector) : Light()
{
	this->type = DIRECTIONAL_LIGHT;
	this->ambient = glm::vec3(0.0, 0.0, 0.0);
	this->color = color;
	this->position = direction;
	this->halfVector = halfVector;
}

void DirectionalLight::Draw(GLuint program)
{
	//TODO Use Uniform Buffer Object? https://www.opengl.org/wiki/Uniform_Buffer_Object
	Light::Draw(program);
	glUniform1i(ids.isEnabled, isEnabled);
	glUniform1i(ids.type, type);
	glUniform3fv(ids.ambient, 1, &ambient[0]);
	glUniform3fv(ids.color, 1, &color[0]);
	glUniform3fv(ids.position, 1, &position[0]);
	glUniform3fv(ids.halfVector, 1, &halfVector[0]);
}

AmbientLight::AmbientLight(glm::vec3 color, float strength) : Light()
{
	this->type = AMBIENT_LIGHT;
	this->color = color * strength;
}

void AmbientLight::Draw(GLuint program)
{
	Light::Draw(program);
	glUniform1i(ids.isEnabled, isEnabled);
	glUniform3fv(ids.ambient, 1, &color[0]);
}

PointLight::PointLight(glm::vec3 color, glm::vec3 position,
	float constantAttenuation, float linearAttenuation, float quadraticAttenuation) : Light()
{
	this->type = POINT_LIGHT;
	this->ambient = glm::vec3(0.0, 0.0, 0.0);
	this->color = color;
	this->position = position;
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}

void PointLight::Draw(GLuint program)
{
	Light::Draw(program);
	glUniform1i(ids.isEnabled, isEnabled);
	glUniform1i(ids.type, type);
	glUniform3fv(ids.ambient, 1, &ambient[0]);
	glUniform3fv(ids.color, 1, &color[0]);
	glUniform3fv(ids.position, 1, &position[0]);
	glUniform1f(ids.constantAttenuation, constantAttenuation);
	glUniform1f(ids.linearAttenuation, linearAttenuation);
	glUniform1f(ids.quadraticAttenuation, quadraticAttenuation);
}

SpotLight::SpotLight(glm::vec3 color, glm::vec3 position,
	glm::vec3 coneDirection, float spotCosCutoff, float spotExponent,
	float constantAttenuation, float linearAttenuation, float quadraticAttenuation) : Light()
{
	this->type = SPOT_LIGHT;
	this->ambient = glm::vec3(0.0, 0.0, 0.0);
	this->color = color;
	this->position = position;
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
	this->coneDirection = coneDirection;
	this->spotCosCutoff = spotCosCutoff;
	this->spotExponent = spotExponent;
}

void SpotLight::Draw(GLuint program)
{
	Light::Draw(program);
	glUniform1i(ids.isEnabled, isEnabled);
	glUniform1i(ids.type, type);
	glUniform3fv(ids.ambient, 1, &ambient[0]);
	glUniform3fv(ids.color, 1, &color[0]);
	glUniform3fv(ids.position, 1, &position[0]);
	glUniform3fv(ids.coneDirection, 1, &coneDirection[0]);
	glUniform1f(ids.spotCosCutoff, spotCosCutoff);
	glUniform1f(ids.spotExponent, spotExponent);
	glUniform1f(ids.constantAttenuation, constantAttenuation);
	glUniform1f(ids.linearAttenuation, linearAttenuation);
	glUniform1f(ids.quadraticAttenuation, quadraticAttenuation);
}