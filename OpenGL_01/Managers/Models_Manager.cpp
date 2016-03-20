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
	Shader_Factory* shaderFactory = Shader_Factory::GetInstance();

	Transform t1 = Transform();
	
	Scene_Container* diablo = CreateModel("diablo", "Examples\\diablo.obj", t1, "Examples\\diablo_diffuse.tga");
	diablo->SetTexture("diablo_normal", Texture_Normal, SOIL_load_OGL_texture(
		"Examples\\diablo_normal.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y));
	diablo->SetTexture("diablo_specular", Texture_Normal, SOIL_load_OGL_texture(
		"Examples\\diablo_specular.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y));

	Light* pointLight1 = new PointLight(
		glm::vec3(1.0, 1.0, 1.0), // color
		glm::vec3(0.0, 0.0, -2.0) // position
		);
	gameLightList["light1"] = pointLight1;

	Light* ambientLight1 = new AmbientLight(glm::vec3(1.0, 1.0, 1.0), 0.1);
	gameLightList["light2"] = ambientLight1;
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
		std::string texture_name = "texture_" + texture_id;
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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void Models_Manager::Update()
{
	// iterate through model list and Update
	for (auto model : gameModelList)
	{
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
		model.second->Draw();
		GLuint current_program = model.second->GetProgram();
		for (auto light : gameLightList)
		{
			light.second->Draw(current_program);
		}
	}
}