#include <iostream>
#include <sstream>
#include <string>
#include "math.h"

#include <SOIL.h>

#include "Models_Manager.h"
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "Shader_Factory.h"
#include "Shadow_Manager.h"

int texture_id = 0;

Models_Manager::Models_Manager()
{
	Shader_Factory* shaderFactory = Shader_Factory::GetInstance();

	Transform t1 = Transform(glm::vec3(0.0f), glm::vec3(0.2f), glm::quat());
	Transform t2 = Transform(glm::vec3(0.0f, 0.1f, 1.0f), glm::vec3(0.02), glm::quat());
	Transform t3 = Transform(glm::vec3(0.0f), glm::vec3(2.0, 0.1, 2.0), glm::quat());
	
	Scene_Container* dog = CreateModel("dog", "Examples\\dog.obj", t2, "Examples\\dog_diffuse.tga");
	dog->SetTexture("dog_normal", Texture_Normal, SOIL_load_OGL_texture(
		"Examples\\dog_normal.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y));
	dog->SetTexture("dog_specular", Texture_Specular, SOIL_load_OGL_texture(
		"Examples\\dog_specular.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y));

	Scene_Container* floor = CreateModel("zfloor", "Examples\\cube.obj", t3, "Examples\\suzanne.dds");
	Scene_Container* box = CreateModel("box", "Examples\\cube.obj", t1, "Examples\\test_texture.png");
	AddLight("light1", new PointLight(
		glm::vec3(1.0, 1.0, 1.0), // color
		glm::vec3(0.0, 2.0, 2.0) // position
	));

	AddLight("ambient1", new AmbientLight(glm::vec3(1.0f), 0.1));
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

void Models_Manager::AddLight(const std::string& name, Light* light)
{
	gameLightList[name] = light;
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
	/*glUseProgram(p);
	for (auto light: gameLightList)
	{
		if (light.second->isEnabled && light.second->castsShadow)
		{
			// Draw scene from light's point of view
			//light.second->DrawShadow(p);
			for (auto model : gameModelList)
			{
				GLuint p = Shadow_Manager::GetProgram();
				glUseProgram(p);
				//model.second->DrawShadow(p);
			}
		}
	}*/

	for (auto model : gameModelList)
	{
		GLuint p = model.second->GetShadowProgram();
		glUseProgram(p);
		for (auto light : gameLightList)
		{
			light.second->DrawShadow(p);
		}
		model.second->DrawShadow();
	}
}