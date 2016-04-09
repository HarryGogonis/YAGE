#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"

Shader_Factory* shaderManager;

int main(int argc, char **argv)
{
	/* http://in2gpu.com/opengl-3/ */

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

	IListener* scene = new Scene_Manager(game_name);
	Init_GLUT::setListener(scene);

	Init_GLUT::run();

	// clean up
	delete scene;
	return 0;
}