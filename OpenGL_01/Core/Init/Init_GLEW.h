#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"

/**********************************************************************************************//**
 * @class	Init_GLEW
 *
 * @brief	Helper class to initalize GLEW
 **************************************************************************************************/

class Init_GLEW
{
public:
	Init_GLEW();
	~Init_GLEW();
	static void Init();
};