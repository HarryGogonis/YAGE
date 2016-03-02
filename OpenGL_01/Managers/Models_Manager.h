#pragma once
#include <map>
#include <iostream>
#include "Shader_Manager.h"
#include "../Rendering/IGameObject.h"

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

	static bool LoadObject(const std::string& path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals,
		std::vector<unsigned short>& out_indices);

private:
	// for big games, use a vector instead of a map
	// map has slow iteration, fast lookup
	std::map <const std::string, IGameObject*> gameModelList;
};