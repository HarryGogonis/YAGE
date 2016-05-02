#pragma once
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "Init_GLEW.h"
#include "../../Managers/Scene_Manager.h"

#include <iostream>

/**********************************************************************************************//**
 * @class	Init_GLUT
 *
 * @brief	Helper class to initalize GLUT and setup listener callbacks
 **************************************************************************************************/

class Init_GLUT
{
public:

	/**********************************************************************************************//**
	 * @fn	static void Init_GLUT::init(const WindowInfo&, const ContextInfo&, const FrameBufferInfo&);
	 *
	 * @brief	Initalizes GLUT with a window
	 **************************************************************************************************/

	static void init(const WindowInfo&, const ContextInfo&, const FrameBufferInfo&);

	static void run();
	static void close();

	void enterFullscreen();
	void exitFullscreen();

	static void printOpenGLInfo(const WindowInfo& window, const ContextInfo& context);
	
	static void setListener(Scene_Manager*& iListener);

private:
	static void idleCallback();

	/**********************************************************************************************//**
	 * @fn	static void Init_GLUT::displayCallback();
	 *
	 * @brief	Callback from GLUT on each frame
	 *
	 * @author	Harry
	 * @date	4/14/2016
	 **************************************************************************************************/

	static void displayCallback();
	static void reshapeCallback(int width, int height);
	static void closeCallback();

	static Scene_Manager* listener;
	static WindowInfo windowInformation;
};
