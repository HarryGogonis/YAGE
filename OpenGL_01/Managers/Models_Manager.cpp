#include <iostream>
#include <sstream>
#include <string>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <SOIL.h>

#include "Models_Manager.h"
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "Shader_Manager.h"

Models_Manager::Models_Manager()
{
	Scene_Container* suzanne = new Scene_Container("Examples\\high_poly.obj");
	// Pay attention to these order of operations (Are they important? I don't know...)
	suzanne->SetProgram(Shader_Manager::GetShader("textureShader"));
	GLuint textureID = SOIL_load_OGL_texture(
		"Examples\\test_texture.png",
		SOIL_LOAD_AUTO,
		1,
		SOIL_FLAG_MIPMAPS);
	suzanne->SetTexture("suzanne", Texture_Diffuse, textureID);
	gameModelList["suzanne"] = suzanne;

	CustomObject* cube1 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube1->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube1->transform.SetScale(glm::vec3(0.2f));
	cube1->transform.SetPosition(glm::vec3(1.0, 0.2, -2.5));
	cube1->Create();
	gameModelList["cube1"] = cube1;

	CustomObject* cube2 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube2->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube2->transform.SetScale(glm::vec3(0.2f));
	cube2->transform.SetPosition(glm::vec3(1.0, 0.2, 2.5));
	cube2->Create();
	gameModelList["cube2"] = cube2;

	CustomObject* cube3 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube3->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube3->transform.SetScale(glm::vec3(0.2f));
	cube3->transform.SetPosition(glm::vec3(-1.0, 0.2, -2.5));
	cube3->Create();
	gameModelList["cube3"] = cube3;

	CustomObject* cube4 = new CustomObject("Examples\\cube.obj", "Examples\\Crate.bmp");
	cube4->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube4->transform.SetScale(glm::vec3(0.2f));
	cube4->transform.SetPosition(glm::vec3(-1.0, 0.2, 2.5));
	cube4->Create();
	gameModelList["cube4"] = cube4;

	// floor
	CustomObject* cube5 = new CustomObject("Examples\\cube.obj", "Examples\\checkerboard.dds");
	cube5->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube5->transform.SetPosition(glm::vec3(0.0, 0.0, 0.0));
	cube5->transform.SetScale(glm::vec3(5.0, 0.0001, 5.0));
	cube5->shininess = 0.5;
	cube5->Create();
	gameModelList["cube5"] = cube5;

	// back wall
	CustomObject* cube6 = new CustomObject("Examples\\cube.obj", "Examples\\checkerboard.dds");
	cube6->SetProgram(Shader_Manager::GetShader("textureShader"));
	cube6->transform.SetPosition(glm::vec3(0.0, 0.0, -5.0));
	cube6->transform.RotateX(90);
	cube5->shininess = 0.5;
	cube6->transform.SetScale(glm::vec3(5.0, 0.0001, 5.0));
	cube6->Create();
	gameModelList["cube6"] = cube6;

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