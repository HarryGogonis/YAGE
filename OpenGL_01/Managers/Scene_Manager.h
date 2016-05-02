#pragma once
#include "Shader_Factory.h"
#include "Models_Manager.h"
#include "Physics_Manager.h"
#include "Shadow_Manager.h"
#include "../Builders/GameObjectsBuilder.h"

class Scene_Manager
{
public:
	Scene_Manager(std::string);
	~Scene_Manager();

	void SetupScene(const GameObjectsBuilder&);

	void UpdatePass() const;
	void ShadowPass() const;
	void RenderPass() const;

	static int GetDeltaTime(); // deltaTime in miliseconds
	static float GetFPS();

	// GLUT callbacks
	void notifyBeginFrame();
	void notifyDisplayFrame();
	void notifyEndFrame();
	void notifyReshape(int width, int height, int p_width, int p_height);
private:
	Shader_Factory* shader_manager;
	Models_Manager* models_manager;
	Shadow_Manager* shadow_manager;
	Physics_Manager* physics_manager;
	Skybox* skybox;

	static int deltaTime, currentTime, lastTime, numFrames;

	std::string scene_name;
};