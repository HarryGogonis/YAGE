#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

struct FrameBufferInfo
{
	unsigned int flags; // https://www.opengl.org/resources/libraries/glut/spec3/node12.html
	bool msaa;			// multisample anti-aliasing
	
	// defaults
	FrameBufferInfo()
	{
		flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
		msaa = false;
	}

	FrameBufferInfo(bool color, bool depth, bool stencil, bool msaa)
	{
		flags = GLUT_DOUBLE; // required;
		if (color) flags |= GLUT_RGBA | GLUT_ALPHA;
		if (depth) flags |= GLUT_DEPTH;
		if (stencil) flags |= GLUT_STENCIL;
		if (msaa) flags |= GLUT_MULTISAMPLE;
		this->msaa = msaa;
	}
};