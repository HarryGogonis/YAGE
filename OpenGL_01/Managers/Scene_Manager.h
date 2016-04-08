#pragma once
#include "Shader_Factory.h"
#include "Models_Manager.h"
#include "../Core/Init/IListener.h"
#include "Shadow_Manager.h"

class Scene_Manager :public IListener
{
public:
	Scene_Manager();
	~Scene_Manager();

	void UpdatePass() const;
	void ShadowPass() const;
	void RenderPass() const;

	// GLUT callbacks
	virtual void notifyBeginFrame() override;
	virtual void notifyDisplayFrame() override;
	virtual void notifyEndFrame() override;
	virtual void notifyReshape(int width, int height,
		int p_width, int p_height) override;

private:
	Shader_Factory* shader_manager;
	Models_Manager* models_manager;
	Shadow_Manager* shadow_manager;
};
