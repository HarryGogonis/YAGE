#pragma once
#include <map>
#include <iostream>
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"

class Models_Manager
{
public:
	Models_Manager();
	~Models_Manager();

	void Draw();
	void DrawShadows();
	void Update();
	/*
	 * We want a controlled creation method to prevent resources from leaking.
	 */
	Scene_Container* CreateModel(
		const std::string& modelName,
		const std::string& modelPath,
		const Transform& transform,
		const std::string& texturePath = "", 
		const TextureType type = Texture_Diffuse);
	void AddLight(const std::string& lightName, Light* light);

	void DeleteModel(const std::string& gameModelName);
	const IGameObject& GetModel(const std::string& gameModelName);

private:
	// for big games, use a vector instead of a map
	// map has slow iteration, fast lookup
	std::map <const std::string, Scene_Container*> gameModelList;
	std::map <const std::string, Light*> gameLightList;
};
