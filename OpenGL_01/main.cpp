	#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"
#include "Builders/GameObjectsBuilder.h"
#include <random>

Shader_Factory* shaderManager;

int main(int argc, char **argv)
{
	std::string game_name = "RAPTOR RAMPAGE";

	/* GLUT Parameters */
	WindowInfo window(
		game_name, // name
		400, 200, // position
		1024, 768,
		true	 // resize
	);

	ContextInfo context(3, 0, true); // OpenGL major, minor, core
	FrameBufferInfo frameBufferinfo(true, true, true, true); // OpenGL buffer flags

	Init_GLUT::init(window, context, frameBufferinfo);

	Scene_Manager* scene = new Scene_Manager(game_name);

	GameObjectsBuilder gob = GameObjectsBuilder();
	
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distrX(-7, 3); // define the range
	std::uniform_int_distribution<> distrZ(-7, 0); // define the range

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
	.addModel("Examples\\diablo.obj", "Examples\\diablo_diffuse.tga")
		.setPosition(glm::vec3(0.f, 0.f, 0.f))
		.setScale(1.f)
		.setRotation(0.f, 180.f, 0.f)
		.addRigidBody(5.f)
		.lockUpright()
		.controlAsPlayer()
		.setDynamic()
	.addLight(OT_LIGHT_POINT)
		.setColor(glm::vec3(0.6f, 0.5f, 0.5f))
		.setPosition(glm::vec3(0.0, 4.0, 0.0))
	.addLight(OT_LIGHT_DIRECTIONAL)
		.setColor(glm::vec3(0.6f, 0.6f, 0.6f))
		.setPosition(glm::vec3(0.f, 0.f, 1.f))
		.setHalfVector(glm::vec3(0.5f, 0.5f, 0.5f))
		.setCastsShadows(false)
	.addLight(OT_LIGHT_AMBIENT)
		.setColor(glm::vec3(1.f, 1.f, 1.f))
		.setStrength(1.0f);

	scene->SetupScene(gob);

	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	// clean up
	delete scene;
	return 0;
}