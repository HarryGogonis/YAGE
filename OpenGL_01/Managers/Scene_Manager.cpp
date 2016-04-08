#include "Scene_Manager.h"
#include "../Rendering/Util/Camera.h"

double currentTime;
double lastTime = 0;
int numFrames;

Scene_Manager::Scene_Manager()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shader_manager = Shader_Factory::GetInstance();

	shadow_manager = Shadow_Manager::GetInstance();

	models_manager = new Models_Manager();
}

Scene_Manager::~Scene_Manager()
{
	delete shader_manager;
	delete models_manager;
}

void Scene_Manager::UpdatePass() const
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	numFrames++;
	if (currentTime - lastTime >= 1.0)
	{
		numFrames = 0;
	}
	Camera::ComputeMatrices();
	models_manager->Update();
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

	// Render scene
	models_manager->Draw();
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
	UpdatePass();
}

void Scene_Manager::notifyDisplayFrame()
{
	ShadowPass();
	RenderPass();
}

void Scene_Manager::notifyEndFrame()
{
	//TODO implement
	lastTime = glutGet(GLUT_ELAPSED_TIME);
}

void Scene_Manager::notifyReshape(int width, int height,
								  int p_width, int p_height)
{
	//TODO implement
}