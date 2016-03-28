#pragma once

// Comment out below line if debug version
//#define RELEASE

#ifdef RELEASE
#define DEBUG_MODE			0
#else
#define DEBUG_MODE			1
#endif

#define CULL_BACK			1
#define DRAW_WIREFRAMES		1