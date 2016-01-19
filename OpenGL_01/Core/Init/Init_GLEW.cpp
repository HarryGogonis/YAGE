#include "Init_GLEW.h"

void Init_GLEW::Init()
{
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: Initalize" << std::endl;
	}

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << "GLEW GL_VERSION_4_3 is supported\n ";
	}
	else
	{
		std::cout << " GLEW GL_VERSION_4_3 not supported\n ";
	}
}