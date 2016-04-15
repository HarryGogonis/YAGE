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

	gob.addModel("Examples\\wall.obj", "Examples\\brick_diffuse.DDS") // Back center
		.setNormal("Examples\\brick_normal.bmp")
		.setSpecular("Examples\\brick_specular.DDS")
		.setPosition(glm::vec3(-3.f, 0.f, 0.f))
		.setScale(8.f)
		.setRotation(90.f, 0.f, 0.f)
		.addRigidBody(0.f);

	gob.addModel("Examples\\wall.obj", "Examples\\dirt.jpg") // Back center
		.setPosition(glm::vec3(-3.f, 7.f, -7.f))
		.setScale(8.f)
		.setRotation(0.f, 0.f, 0.f)
		.addRigidBody(0.f);
	
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distrX(-7, 3); // define the range
	std::uniform_int_distribution<> distrZ(-7, 0); // define the range

	gob.addModel("Examples\\diablo.obj", "Examples\\diablo_diffuse.tga")
		.setNormal("Examples\\diablo_normal.tga")
		.setSpecular("Examples\\diablo_specular.tga")
		.setPosition(glm::vec3(distrX(eng), 0.f, distrZ(eng)))
		.setScale(0.01f)
		.setRotation(0.f, 0.0f, 0.f)
		.addRigidBody(5.f)
		.lockUpright();

	for (int i = 0; i < 100; i++)
	{
		gob.copyModel()
			.setPosition(glm::vec3(distrX(eng), 0.f, distrZ(eng)))
			.setScale(0.1f)
			.setRotation(0.f, 0.0f, 0.f)
			.addRigidBody(5.f)
			.lockUpright();
	}

	gob.addLight(OT_LIGHT_POINT)
		.setColor(glm::vec3(0.6f, 0.5f, 0.5f))
		.setPosition(glm::vec3(0.0, 4.0, 0.0));

	gob.addLight(OT_LIGHT_DIRECTIONAL)
		.setColor(glm::vec3(0.9f, 0.9f, 0.9f))
		.setPosition(glm::vec3(0.f, 0.1f, 1.f))
		.setHalfVector(glm::vec3(0.5f, 0.5f, 0.5f))
		.setCastsShadows(true);

	gob.addLight(OT_LIGHT_AMBIENT)
		.setColor(glm::vec3(1.f, 1.f, 1.f))
		.setStrength(0.1f);

	gob.addParticleSystem("Examples\\particle.DDS");

	scene->SetupScene(gob);

	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	// clean up
	delete scene;
	return 0;
}