#pragma once

// Comment out below line if debug version
#define RELEASE

#ifdef RELEASE
#define DEBUG_MODE			0
#define DRAW_WIREFRAMES		0
#else
#define DEBUG_MODE			1
#define DRAW_WIREFRAMES		1
#endif

#define CULL_BACK			0
#define FPS_COUNTER			1