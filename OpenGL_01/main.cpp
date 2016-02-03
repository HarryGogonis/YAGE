#include "Core\Init\Init_GLUT.h"
#include "Managers\Scene_Manager.h"

Shader_Manager* shaderManager;

int main(int argc, char **argv)
{
	/* http://in2gpu.com/opengl-3/ */

	/* GLUT Parameters */
	WindowInfo window(
		std::string("Beginner tutorial"), // name
		400, 200, // position
		800, 600, // size
		true	 // resize
	);
	ContextInfo context(4, 3, true); // OpenGL major, minor, core
	FrameBufferInfo frameBufferinfo(true, true, true, true); // OpenGL buffer flags

	Init_GLUT::init(window, context, frameBufferinfo);

	IListener* scene = new Scene_Manager();
	Init_GLUT::setListener(scene);

	Init_GLUT::run();
	
	// clean up
	delete scene;
	return 0;
}