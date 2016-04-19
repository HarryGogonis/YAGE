#include "Scene_Manager.h"
#include "../Rendering/Util/Camera.h"
#include "../Core/Options.h"
#include "../Core/Init/WindowInfo.h"

int Scene_Manager::lastTime = 0;
int Scene_Manager::deltaTime = 0;
int Scene_Manager::currentTime = 0;
int Scene_Manager::numFrames = 0;

Scene_Manager::Scene_Manager(std::string scene_name)
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (CULL_BACK)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	this->scene_name = scene_name;
	shader_manager = Shader_Factory::GetInstance();
	shadow_manager = Shadow_Manager::GetInstance();
	physics_manager = Physics_Manager::GetInstance();
	skybox = Skybox::GetInstance();
}

Scene_Manager::~Scene_Manager()
{
	delete physics_manager;
	delete shader_manager;
	delete models_manager;
	delete shadow_manager;
}

void Scene_Manager::SetupScene(const GameObjectsBuilder& gob)
{
	models_manager = gob.getResult();
}

void Scene_Manager::UpdatePass() const
{
	physics_manager->Step();
	models_manager->Update();
	skybox->Update();
}


void Scene_Manager::RenderPass() const
{
	// Restore default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Restore default viewport
	glViewport(0, 0, 1024, 768); //TODO Don't hardcode

	// Clear scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	physics_manager->DrawDebug();
	models_manager->Draw();
	skybox->Draw();

}

int Scene_Manager::GetDeltaTime()
{
	return deltaTime;
}

float Scene_Manager::GetFPS()
{
	return numFrames*1000.0 / (currentTime - lastTime);
}

void Scene_Manager::ShadowPass() const
{
	// Switch to shadow frame buffer
	shadow_manager->BindForWriting();

	// Render on the whole framebuffer
	glViewport(0, 0, shadow_manager->DEPTH_TEXTURE_SIZE, shadow_manager->DEPTH_TEXTURE_SIZE);

	// Clear the screen
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Enable polygon offset to resolve depth-fighting issues
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 4.0f);

	// Render scene
	models_manager->DrawShadows();

	glDisable(GL_POLYGON_OFFSET_FILL);

}

void Scene_Manager::notifyBeginFrame()
{
	currentTime = double(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = currentTime - lastTime;
	numFrames++;
	if (deltaTime >= 1000)
	{
		if (FPS_COUNTER)
		{
			printf("\rFPS: %4.2f", GetFPS());
		}
		numFrames = 0;
		lastTime = currentTime;
	}

	UpdatePass();
}

void Scene_Manager::notifyDisplayFrame()
{
	ShadowPass();
	RenderPass();
}

void Scene_Manager::notifyEndFrame()
{
}

void Scene_Manager::notifyReshape(int width, int height,
								  int p_width, int p_height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera::resizeWindow(width, height);
	// TODO: Pay attention to position
}