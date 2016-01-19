#pragma once
/*
 * Listener is a an interface for things that effect a frame
 */

class IListener // interface
{
public:
	virtual ~IListener() = 0;

	// drawing functions
	virtual void notifyBeginFrame() = 0;
	virtual void notifyDisplayFrame() = 0;
	virtual void notifyEndFrame() = 0;
	virtual void notifyReshape(int width, int height,
		int p_width, int p_height) = 0;
};

inline IListener::~IListener()
{

}