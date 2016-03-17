#include <iostream>
#include <sstream>
#include <string>

#include <SOIL.h>

#include "Models_Manager.h"
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "Shader_Manager.h"

Models_Manager::Models_Manager()
{
	Transform t = Transform();
	Transform t2 = Transform(glm::vec3(-10.0f, 5.0f, 4.0f), glm::vec3(1.0f), glm::quat());
	Scene_Container* suzanne = new Scene_Container("Examples\\suzanne.obj", t);
	Scene_Container* raptor_2 = new Scene_Container("Examples\\Raptor.obj", t2);
	// Pay attention to these order of operations (Are they important? I don't know...)
	suzanne->SetProgram(Shader_Manager::GetShader("textureShader"));
	raptor_2->SetProgram(Shader_Manager::GetShader("textureShader"));
	GLuint uvTexture = SOIL_load_OGL_texture(
		"Examples\\test_texture.png",
		SOIL_LOAD_AUTO,
		1,
		SOIL_FLAG_MIPMAPS);
	GLuint raptor_skin = SOIL_load_OGL_texture(
		"Examples\\raptor.jpg",
		SOIL_LOAD_AUTO,
		1,
		SOIL_FLAG_MIPMAPS);
	suzanne->SetTexture("suzanne", Texture_Diffuse, uvTexture);
	raptor_2->SetTexture("raptor", Texture_Diffuse, raptor_skin);
	gameModelList["suzanne"] = suzanne; 
	gameModelList["raptor2"] = raptor_2;

	Light* pointLight1 = new PointLight(
		glm::vec3(0.6, 0.5, 0.5), // color
		glm::vec3(0.0, 4.0, 0.0) // position
		); 
	pointLight1->SetProgram(Shader_Manager::GetShader("textureShader"));
	pointLight1->SetAttenuation(0.0, 0.0, 1.0);
	pointLight1->Create();
	gameModelList["light1"] = pointLight1;

	Light* directionalLight1 = new DirectionalLight(
		glm::vec3(0.2, 0.2, 0.2), // color
		glm::vec3(0.0, 0.0, 1.0), // direction
		glm::vec3(0.5, 0.5, 0.5) // half vec
		);
	directionalLight1->SetProgram(Shader_Manager::GetShader("textureShader"));
	directionalLight1->Create();
	gameModelList["light2"] = directionalLight1;

	Light* ambientLight1 = new AmbientLight(glm::vec3(1.0, 1.0, 1.0), 0.05);
	ambientLight1->SetProgram(Shader_Manager::GetShader("textureShader"));
	ambientLight1->Create();
	gameModelList["light3"] = ambientLight1;
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
	}
}

void Models_Manager::Draw()
{
	// iterate through model list and Draw
	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}