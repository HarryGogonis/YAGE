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

	gob.addModel("Examples\\diablo.obj", "Examples\\diablo_diffuse.tga")
		.setPosition(glm::vec3(distrX(eng), 0.f, distrZ(eng)))
		.setScale(2.0f)
		.setRotation(0.f, 0.0f, 0.f);

	gob.addLight(OT_LIGHT_AMBIENT)
		.setColor(glm::vec3(1.f, 1.f, 1.f))
		.setStrength(1.0f);

	scene->SetupScene(gob);

	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	// clean up
	delete scene;
	return 0;
}