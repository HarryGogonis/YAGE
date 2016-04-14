#pragma once
#include <map>
#include <iostream>
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "../Rendering/Models/Particle_Container.h"

class Models_Manager
{
public:
	Models_Manager();
	~Models_Manager();

	void Draw();
	void DrawShadows();
	void Update();
	void addLight(Light* light);
	/*
	 * We want a controlled creation method to prevent resources from leaking.
	 */
	Scene_Container* CreateModel(
		const std::string& modelPath,
		const Transform& transform,
		const std::string& texturePath = "", 
		const TextureType type = Texture_Diffuse);
	Particle_Container* CreateParticleSystem(Transform t, const std::string& texturePath);

private:
	// for big games, use a vector instead of a map
	// map has slow iteration, fast lookup
	std::vector <Scene_Container*> gameModelList;
	std::vector <Particle_Container*> gameParticleList;
	std::vector <Light*> gameLightList;
};
