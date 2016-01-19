#pragma once
#include <map>
#include "Shader_Manager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"

class Models_Manager
{
public:
	Models_Manager();
	~Models_Manager();

	void Draw();
	void Update();
	//void CreateModel(const std::string& gameModelName);
	void DeleteModel(const std::string& gameModelName);
	const IGameObject& GetModel(const std::string& gameModelName);

private:
	// for big games, use a vector instead of a map
	// map has slow iteration, fast lookup
	std::map <const std::string, IGameObject*> gameModelList;
};