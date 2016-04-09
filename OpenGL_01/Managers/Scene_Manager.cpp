#include "Scene_Manager.h"
#include "../Rendering/Util/Camera.h"
#include "../Core/Options.h"
#include "../Builders/GameObjectsBuilder.h"
#include "../Core/Init/WindowInfo.h"

double currentTime;
double lastTime = 0;
int numFrames;

Scene_Manager::Scene_Manager(std::string scene_name)
{
	if (CULL_BACK)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	this->scene_name = scene_name;
	shader_manager = Shader_Factory::GetInstance();
	physics_manager = Physics_Manager::GetInstance();
	GameObjectsBuilder gob = GameObjectsBuilder();

	gob.addModel("Examples\\wall.obj", "Examples\\bricks.jpg") // Back center
			.setPosition(glm::vec3(-3.f, 0.f, 0.f))
			.setScale(8.f)
			.setRotation(90.f, 0.f, 0.f)
			.addRigidBody(0.f)
		.addModel("Examples\\wall.obj", "Examples\\dirt.jpg") // Back center
			.setPosition(glm::vec3(-3.f, 7.f, -7.f))
			.setScale(8.f)
			.setRotation(0.f, 0.f, 0.f)
			.addRigidBody(0.f)
		.addModel("Examples\\Raptor.obj", std::string())
			.setPosition(glm::vec3(0.f, 0.f, 0.f))
			.setScale(1.f)
			.setRotation(0.f, 180.f, 0.f)
			.addRigidBody(5.f)
			.lockUpright()
		.addLight(OT_LIGHT_POINT)
			.setColor(glm::vec3(0.6f, 0.5f, 0.5f))
			.setPosition(glm::vec3(0.0, 4.0, 0.0))
		.addLight(OT_LIGHT_DIRECTIONAL)
			.setColor(glm::vec3(0.2f, 0.2f, 0.2f))
			.setPosition(glm::vec3(0.f, 0.f, 1.f))
			.setHalfVector(glm::vec3(0.5f, 0.5f, 0.5f))
		.addLight(OT_LIGHT_AMBIENT)
			.setColor(glm::vec3(1.f, 1.f, 1.f))
			.setStrength(0.2f);


	models_manager = gob.getResult();
}

Scene_Manager::~Scene_Manager()
{
	delete physics_manager;
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
	physics_manager->Step();
	models_manager->Update();
}

void Scene_Manager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	physics_manager->DrawDebug();
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