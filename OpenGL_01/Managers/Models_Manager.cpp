#include <iostream>
#include <sstream>
#include <string>
#include "math.h"

#include <SOIL.h>

#include "Models_Manager.h"
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "Shader_Factory.h"

int texture_id = 0;

Models_Manager::Models_Manager()
{

}

Models_Manager::~Models_Manager()
{
	// iterate through map
	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

// TODO: Create Light method
Scene_Container* Models_Manager::CreateModel(
	const std::string& modelName,
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
		std::string texture_name;
		if (type == Texture_Diffuse)
			texture_name = modelName + "_diffuse";
		else if (type == Texture_Specular)
			texture_name = modelName + "_specular";
		else
			texture_name = modelName + "_normal";
		GLuint texture = SOIL_load_OGL_texture(
			texturePath.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y);
		if (!texture)
			std::cout << "ERROR: texture for model not loaded properly" << std::endl;
		else
			model->SetTexture(texture_name, type, texture);
	}
	gameModelList[modelName] = model;
	return model;
}

Light* Models_Manager::AddLight(const std::string& name, Light* light)
{
	gameLightList[name] = light;
	return light;
}

void Models_Manager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);
}

const IGameObject& Models_Manager::GetModel(const std::string& gameModelName)
{
	return (*gameModelList.at(gameModelName));
}

void Models_Manager::Update()
{
	// iterate through model list and Update
	for (auto model : gameModelList)
	{
		glUseProgram(model.second->GetProgram());
		model.second->Update();

		for (auto light : gameLightList)
		{
			light.second->Update();
		}
	}

}

void Models_Manager::Draw()
{
	// iterate through model list and Draw
	for (auto model : gameModelList)
	{
		GLuint p = model.second->GetProgram();
		glUseProgram(p);
		model.second->Draw();
		for (auto light : gameLightList)
		{
			light.second->Draw(p);
		}
	}
}

void Models_Manager::DrawShadows()
{
	for (auto model : gameModelList)
	{
		GLuint p = model.second->GetShadowProgram();
		glUseProgram(p);
		for (auto light : gameLightList)
		{
			// NOTE We will end up only drawing 1 light
			light.second->DrawShadow(p);
		}
		model.second->DrawShadow();
	}
}