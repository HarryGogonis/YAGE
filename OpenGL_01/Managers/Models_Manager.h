#pragma once
#include <iostream>
#include <vector>
#include "../Rendering/Util/Light.h"
#include "../Rendering/Models/Scene_Container.h"
#include "../Rendering/Models/Particle_Container.h"

/**********************************************************************************************//**
 * @class	Models_Manager
 *
 * @brief	Manager for all models in a scene.
 *
 **************************************************************************************************/

class Models_Manager
{
public:
	Models_Manager();
	~Models_Manager();

	/**********************************************************************************************//**
	 * @fn	void Models_Manager::Draw();
	 *
	 * @brief	The Scene_Manager will call this method.
	 * 			Notifies all the Scene_Container, Particle_System, and Light to draw.
	 **************************************************************************************************/

	void Draw();

	/**********************************************************************************************//**
	 * @fn	void Models_Manager::DrawShadows();
	 *
	 * @brief	The Scene_Manager will call this method.
	 * 			Notifies all the Scene_Container, Particle_System, and Light to draw shadows.
	 **************************************************************************************************/

	void DrawShadows();

	/**********************************************************************************************//**
	 * @fn	void Models_Manager::Update();
	 *
	 * @brief	The Scene_Manager will call this method.
	 * 			Notifies all the Scene_Container, Particle_System, and Light to Draw().
	 **************************************************************************************************/

	void Update();

	/**********************************************************************************************//**
	 * @fn	void Models_Manager::addLight(Light*& light);
	 *
	 * @brief	Adds a light to the light list.
	 *
	 * @param light	If non-null, the light.
	 **************************************************************************************************/

	void addLight(Light* light);

	/**********************************************************************************************//**
	 * @fn	Scene_Container* Models_Manager::CreateModel( const std::string& modelPath, const Transform& transform, const std::string& texturePath = "", const TextureType type = Texture_Diffuse);
	 *
	 * @brief	Creates a model and adds it to the model list
	 *
	 * @param	modelPath  	Full pathname to the object file.
	 * @param	transform  	The transform.
	 * @param	texturePath	Full pathname to the texture file.
	 * @param	type	   	The texture type.
	 *
	 * @return	null if it fails, else the new model.
	 **************************************************************************************************/

	Scene_Container* CreateModel(
		const std::string& modelPath,
		const Transform& transform,
		const std::string& texturePath = "", 
		const TextureType type = Texture_Diffuse);

	/**********************************************************************************************//**
	 * @fn	Scene_Container* Models_Manager::CreateModel(const Scene_Container*& otherModel, const Transform& transform);
	 *
	 * @brief	Copies a model and adds it to the model list
	 *
	 * @param	otherModel	The other model.
	 * @param	transform 	The transform.
	 *
	 * @return	null if it fails, else the new model.
	 **************************************************************************************************/

	Scene_Container* CreateModel(const Scene_Container*& otherModel, const Transform& transform);

	/**********************************************************************************************//**
	 * @fn	Particle_Container* Models_Manager::CreateParticleSystem(Transform t, const std::string& texturePath);
	 *
	 * @brief	Creates particle system and adds it to the particle list
	 *
	 * @param	transform	The Transform
	 * @param	texturePath	Full pathname to the texture file.
	 *
	 * @return	null if it fails, else the new particle system.
	 **************************************************************************************************/

	Particle_Container* CreateParticleSystem(Transform transform, const std::string& texturePath);

private:
	std::vector <Scene_Container*> gameModelList;
	std::vector <Particle_Container*> gameParticleList;
	std::vector <Light*> gameLightList;
};
