#include "Models_Manager.h"

Models_Manager::Models_Manager()
{
	Quad* quad1 = new Quad(Transform(
		glm::vec4(0, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		), Color::RED);
	quad1->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad1->Create();
	gameModelList["quad1"] = quad1;

	Quad* quad2 = new Quad(Transform(
		glm::vec4(5, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		), Color::RED);
	quad2->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad2->Create();
	gameModelList["quad2"] = quad2;

	Quad* quad3 = new Quad(Transform(
		glm::vec4(-5, 0, 0, 1),
		glm::vec4(1, 1, 1, 1),
		Quaternion()
		), Color::RED);
	quad3->SetProgram(Shader_Manager::GetShader("colorShader"));
	quad3->Create();
	gameModelList["quad3"] = quad3;
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