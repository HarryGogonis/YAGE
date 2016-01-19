#pragma once
#include "Shader_Manager.h"
#include "Models_Manager.h"
#include "../Core/Init/IListener.h"

class Scene_Manager :public IListener
{
public:
	Scene_Manager();
	~Scene_Manager();

	virtual void notifyBeginFrame();
	virtual void notifyDisplayFrame();
	virtual void notifyEndFrame();
	virtual void notifyReshape(int width, int height,
		int p_width, int p_height);

private:
	Shader_Manager* shader_manager;
	Models_Manager* models_manager;
};