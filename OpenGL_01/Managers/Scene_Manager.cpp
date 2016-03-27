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

	shader_manager->CreateProgram("textureShader",
		"Shaders\\TextureVertexShader.glsl",
		"Shaders\\TextureFragmentShader.glsl");
	models_manager = new Models_Manager();
}

Scene_Manager::~Scene_Manager()
{
	delete shader_manager;
	delete models_manager;
}

void Scene_Manager::notifyBeginFrame()
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

void Scene_Manager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	models_manager->Draw();
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