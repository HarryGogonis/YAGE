#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"
#include "Builders/GameObjectsBuilder.h"
#include <random>

Shader_Factory* shaderManager;

int main(int argc, char **argv)
{
	std::string game_name = "DEMO";

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

	gob.addModel("Assets\\quad.obj", "Assets\\grass\\ls_grass.jpg")
		.setSpecular("Assets\\grass\\ls_grass_spec.jpg")
		.setPosition(glm::vec3(0.f, 0.f, 0.f))
		.setRotation(90.f, 0.f, 0.f)
		.setScale(10.f)
		.addRigidBody(0.f)
		.copyModel()
		.setPosition(glm::vec3(-30.f, 0.f, 0.f))
		.setScale(10.f)
		.addRigidBody(0.f);

	gob.addModel("Assets\\cat\\cat.obj")
		.setPosition(0.f, 5.f, 0.f)
		.setRotation(0.0f, 0.0f, 0.0f)
		.setScale(1.f)
		.addRigidBody(5.f)
		.lockUpright()
		.setDynamic();
	gob.copyModel()
		.setPosition(2.5f, 5.f, -2.f)
		.setRotation(0.0f, 0.0f, 0.0f)
		.setScale(1.f)
		.addRigidBody(5.f)
		.lockUpright()
		.setDynamic();
	gob.copyModel()
		.setPosition(1.f, 5.f, 1.f)
		.setRotation(0.0f, 0.0f, 0.0f)
		.setScale(1.f)
		.addRigidBody(5.f)
		.lockUpright()
		.setDynamic();

	gob.addModel("Assets\\cube.obj", "Assets\\wall\\brick_diffuse.DDS")
		.setNormal("Assets\\wall\\brick_normal.bmp")
		.setSpecular("Assets\\wall\\brick_specular.DDS")
		.setPosition(glm::vec3(-10.f, 1.f, 0.f))
		.setRotation(90.f, 0.f, 0.f)
		.setScale(1.f)
		.addRigidBody(5.f)
		.lockUpright()
		.setDynamic();

	gob.addModel("Assets\\trees\\tree01.3ds")
		.setPosition(5.f, 0.f, -4.f)
		.setRotation(-90.0f, 0.0f, 0.0f)
		.setScale(5.f)
		.addRigidBody(0.f);

	gob.addModel("Assets\\woodenbridge.obj", "Assets\\environment\\T_HighShack_D.tga")
		.setNormal("Assets\\environment\\T_HighShack_N.tga")
		.setSpecular("Assets\\environment\\T_HighShack_S.tga")
		.setPosition(15.f, -1.f, 0.f)
		.setRotation(0.f, 0.f, 0.f)
		.setScale(1.f)
		.addRigidBody(0.f);

	gob.addModel("Assets\\environment\\HighShack.obj", "Assets\\environment\\T_HighShack_D.tga")
		.setNormal("Assets\\environment\\T_HighShack_N.tga")
		.setSpecular("Assets\\environment\\T_HighShack_S.tga")
		.setPosition(-7.f, 0.f, -10.f)
		.setScale(3.f)
		.addRigidBody(0.f);

	gob.addModel("Examples\\diablo.obj", "Examples\\diablo_diffuse.tga")
		.setNormal("Examples\\diablo_normal.tga")
		.setSpecular("Examples\\diablo_specular.tga")
		.setPosition(glm::vec3(-5.f, 10.f, 0.f))
		.setScale(1.f)
		.setRotation(0.f, 45.f, 0.f)
		.addRigidBody(1000.f)
		.lockUpright()
		.controlAsPlayer()
		.setDynamic();

	gob.addParticleSystem("").
		setPosition(-15.f, 0.f, 3.f);

		gob.addLight(OT_LIGHT_DIRECTIONAL)
		.setColor(glm::vec3(0.8f, 0.8f, 0.8f))
		.setPosition(glm::vec3(1.0f, 1.0f, 0.0f))
		.setHalfVector(glm::vec3(0.5f, 0.5f, 0.5f))
		.setCastsShadows(true)
		.addLight(OT_LIGHT_AMBIENT)
		.setColor(glm::vec3(1.f, 1.f, 1.f))
		.setStrength(0.3f);

	scene->SetupScene(gob);

	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	// clean up
	delete scene;
	return 0;
}