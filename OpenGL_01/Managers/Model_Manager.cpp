#include "Models_Manager.h"

Models_Manager::Models_Manager()
{
	//TODO more elegant solution, AKA method for creating models
	// triangle game object
	Transform t2 = Transform(
		Vector4(0, 0, 0),
		Vector4(0.5, 0.5, 1),
		Quaternion(1.0, 0.5, 0.5, 0.5)
	);

	Quad* quad = new Quad(t2, Color::RED);
	quad->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad->Create();
	gameModelList["quad"] = quad;
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