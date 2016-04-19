#include <iostream>
#include <sstream>
#include <string>
#include "math.h"

#include <SOIL.h>

#include "Models_Manager.h"
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "Shader_Factory.h"
#include "../Rendering/Models/Particle_Container.h"
#include "../Rendering/Util/TextureLoader.h"

int texture_id = 0;

Models_Manager::Models_Manager()
{}

Models_Manager::~Models_Manager()
{
	// iterate through map
	for (auto model : gameModelList)
	{
		delete model;
	}
	gameModelList.clear();

	for (auto particle : gameParticleList)
	{
		delete particle;
	}
	gameParticleList.clear();
}

// TODO: Create Light method
Scene_Container* Models_Manager::CreateModel(
	const std::string& modelPath,
	const Transform& transform,
	const std::string& texturePath,
	const TextureType type)
{
	Scene_Container* model = new Scene_Container(modelPath, transform);
	Shader_Factory* shaderFactory = Shader_Factory::GetInstance();
	shaderFactory->SetTextureShader(*model);
	if (!texturePath.empty())
	{
		GLuint texture = TextureLoader::LoadTexture(texturePath);
		std::string texture_name = "texture_" + texture_id;
		if (texture)
			model->SetTexture(texture_name, type, texture);
	}
	gameModelList.push_back(model);
	return model;
}

Scene_Container* Models_Manager::CreateModel(const Scene_Container*& other, const Transform& transform)
{
	Scene_Container* model = new Scene_Container(other, transform);
	Shader_Factory* shaderFactory = Shader_Factory::GetInstance();
	shaderFactory->SetTextureShader(*model);
	gameModelList.push_back(model);
	return model;
}

Particle_Container* Models_Manager::CreateParticleSystem(Transform t, const std::string& texturePath)
{
	Particle_Container* particle = new Particle_Container(t, texturePath);
	gameParticleList.push_back(particle);
	return particle;
}

void Models_Manager::Update()
{
	// iterate through model list and Update
	for (auto model : gameModelList)
	{
		glUseProgram(model->GetProgram());
		model->Update();

		for (auto light : gameLightList)
		{
			light->Update();
		}
	}
	
	for (auto particle : gameParticleList)
	{
		particle->Update();
	}
}

void Models_Manager::addLight(Light * light)
{
	gameLightList.push_back(light);
}

void Models_Manager::Draw()
{
	// iterate through model list and Draw
	for (auto model : gameModelList)
	{
		GLuint p = model->GetProgram();
		glUseProgram(p);
		model->Draw(p);
		for (auto light : gameLightList)
		{
			light->Draw(p);
		}
	}

	for (auto particle : gameParticleList)
	{
		particle->Draw();
	}
}

void Models_Manager::DrawShadows()
{
	for (auto model : gameModelList)
	{
		GLuint p = model->GetShadowProgram();
		glUseProgram(p);
		for (auto light : gameLightList)
		{
			// NOTE We will end up only drawing 1 light
			light->DrawShadow(p);
		}
		model->DrawShadow(p);
	}
}