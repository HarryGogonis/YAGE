#pragma once
#include <string>

/**********************************************************************************************//**
 * @struct	WindowInfo
 *
 * @brief	Information about the game window.
 *
 * @author	Harry
 * @date	4/14/2016
 **************************************************************************************************/

struct WindowInfo
{
	std::string name;
	int width, height;
	int position_x, position_y;
	bool isReshapable;

	// Default constructor
	WindowInfo()
	{
		name = "OpenGL tutorial";
		width = 800; height = 600;
		position_x = 300;
		position_y = 300;
		isReshapable = true;
	}

	// Param constructor
	WindowInfo(std::string name,
		int position_x, int position_y,
		int width, int height,
		bool isReshapable)
	{
		this->name = name;
		this->position_x = position_x;
		this->position_y = position_y;
		this->width = width;
		this->height = height;
		this->isReshapable = isReshapable;
	}

	// Copy constructor
	WindowInfo(const WindowInfo& windowInfo)
	{
		name = windowInfo.name;
		position_x = windowInfo.position_x;
		position_y = windowInfo.position_y;
		width = windowInfo.width;
		height = windowInfo.height;
		isReshapable = windowInfo.isReshapable;
	}

	// Overload assignment operator
	void operator=(const WindowInfo& windowInfo)
	{
		name = windowInfo.name;
		position_x = windowInfo.position_x;
		position_y = windowInfo.position_y;
		width = windowInfo.width;
		height = windowInfo.height;
		isReshapable = windowInfo.isReshapable;
	}
};