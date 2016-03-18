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
	Transform t = Transform();
	Transform t2 = Transform(glm::vec3(-1.0f, 2.0f, -2.0f), glm::vec3(0.6f), glm::quat());
	Transform t3 = Transform(glm::vec3(-1.0f, 2.0f, 2.0f), glm::vec3(0.01f), glm::quat());

	t3.RotateY(25);
	CreateModel("suzanne", "Examples\\suzanne.obj", t2, "Examples\\test_texture.png");
	CreateModel("raptor", "Examples\\Raptor.obj", t3, "Examples\\raptor.jpg");

	Light* pointLight1 = new PointLight(
		glm::vec3(0.6, 0.5, 0.5), // color
		glm::vec3(0.0, 4.0, 0.0) // position
		);
	gameLightList["light1"] = pointLight1;

	Light* directionalLight1 = new DirectionalLight(
		glm::vec3(0.2, 0.2, 0.2), // color
		glm::vec3(0.0, 0.0, 1.0), // direction
		glm::vec3(0.5, 0.5, 0.5) // half vec
		);
	gameLightList["light2"] = directionalLight1;

	Light* ambientLight1 = new AmbientLight(glm::vec3(1.0, 1.0, 1.0), 0.2);
	gameLightList["light3"] = ambientLight1;
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
void Models_Manager::CreateModel(
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
			SOIL_FLAG_MIPMAPS);
		if (!texture)
			std::cout << "ERROR: texture for model not loaded properly" << std::endl;
		else
			model->SetTexture(texture_name, type, texture);
	}
	gameModelList[modelName] = model;
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