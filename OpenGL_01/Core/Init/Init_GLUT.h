#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "Init_GLEW.h"
#include "../../Managers/Scene_Manager.h"

#include <iostream>

class Init_GLUT
{
public:
	static void init(const WindowInfo&, const ContextInfo&, const FrameBufferInfo&);

	static void run();
	static void close();

	void enterFullscreen();
	void exitFullscreen();

	static void printOpenGLInfo(const WindowInfo& window, const ContextInfo& context);
	
	static void setListener(Scene_Manager*& iListener);

private:
	// GLUT callbacks
	static void idleCallback();
	static void displayCallback();
	static void reshapeCallback(int width, int height);
	static void closeCallback();

	static Scene_Manager* listener;
	static WindowInfo windowInformation;
};
