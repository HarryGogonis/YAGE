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
	std::uniform_int_distribution<> distrX(-7, 3);		// Range of X position
	std::uniform_int_distribution<> distrZ(-7, 0);		// Range of Z position
	std::uniform_int_distribution<> distrYDog(8, 50);	// Range of dog's Y position
	std::uniform_int_distribution<> rotationY(0, 359);	// Range of Y rotation


	gob.addModel("Assets\\wall.obj", "Assets\\brick_diffuse.DDS") // Back center
		.setNormal("Assets\\brick_normal.bmp")
		.setSpecular("Assets\\brick_specular.DDS")
		.setPosition(-3.f, 0.f, 0.f)
		.setScale(8.f)
		.setRotation(90.f, 0.f, 0.f)
		.addRigidBody(0.f);

	gob.addModel("Assets\\wall.obj", "Assets\\dirt.jpg") // Back center
		.setPosition(-3.f, 7.f, -7.f)
		.setScale(8.f)
		.addRigidBody(0.f);

	gob.addModel("Assets\\diablo.obj", "Assets\\diablo_diffuse.tga")
		.setNormal("Assets\\diablo_normal.tga")
		.setSpecular("Assets\\diablo_specular.tga")
		.setPosition(distrX(eng), 0.f, distrZ(eng))
		.addRigidBody(5.f)
		.lockUpright();

	for (int i = 0; i < 10; i++)
	{
		gob.copyModel()
			.setPosition(distrX(eng), 0.f, distrZ(eng))
			.setScale(0.75f)
			.setRotation(0.f, rotationY(eng), 0.f)
			.addRigidBody(5.f)
			.lockUpright();
	}

	gob.addModel("Assets\\dog.obj", "Assets\\dog_diffuse.tga")
		.setNormal("Examples\\dog_normal.tga")
		.setPosition(distrX(eng), distrYDog(eng), distrZ(eng))
		.setRotation(0.f, rotationY(eng), 0.f)
		.addRigidBody(4.f);

	for (int i = 0; i < 10; i++)
	{
		gob.copyModel()
			.setPosition(distrX(eng), distrYDog(eng), distrZ(eng))
			.setRotation(0.f, rotationY(eng), 0.f)
			.addRigidBody(4.f);
	}

	gob.addLight(OT_LIGHT_POINT)
		.setColor(glm::vec3(0.6f, 0.5f, 0.5f))
		.setPosition(0.0, 4.0, 0.0);

	gob.addLight(OT_LIGHT_DIRECTIONAL)
		.setColor(glm::vec3(0.9f, 0.9f, 0.9f))
		.setPosition(0.f, 0.1f, 1.f)
		.setHalfVector(glm::vec3(0.5f, 0.5f, 0.5f))
		.setCastsShadows(true);

	gob.addLight(OT_LIGHT_AMBIENT)
		.setColor(glm::vec3(1.f, 1.f, 1.f))
		.setStrength(0.1f);

	scene->SetupScene(gob);

	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	// clean up
	delete scene;
	return 0;
}