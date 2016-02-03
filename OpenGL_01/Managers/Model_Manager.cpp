#include "Models_Manager.h"

Models_Manager::Models_Manager()
{
	Triangle* triangle1 = new Triangle(Transform(
		Vector3(-25, 25, 0),
		Vector3(0.5, 0.5, 1),
		Quaternion()), Color::Darken(Color::GREEN, 0.3));
	triangle1->SetProgram(Shader_Manager::GetShader("colorShader"));
	triangle1->Create();
	gameModelList["triangle1"] = triangle1;

	Triangle* triangle2 = new Triangle(Transform(
		Vector3(25, 25, 50),
		Vector3(1, 1, 1),
		Quaternion()), Color::Darken(Color::GREEN, 0.3));
	triangle2->SetProgram(Shader_Manager::GetShader("colorShader"));
	triangle2->Create();
	gameModelList["triangle2"] = triangle2;

	Quad* quad1 = new Quad(Transform(
		Vector3(0, 0, -100),
		Vector3(2, 0.25, 1),
		Quaternion()), Color::HSV(0.45, 0.60, 0.20));
	quad1->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad1->Create();
	gameModelList["quad1"] = quad1;
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