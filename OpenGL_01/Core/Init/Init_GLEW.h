#pragma once
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"

class Init_GLEW
{
public:
	Init_GLEW();
	~Init_GLEW();
	static void Init();
};