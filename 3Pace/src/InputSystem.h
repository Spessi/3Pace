#pragma once

#include "System.h"
#include "IntentComponent.h"
#include "SDLHelper.h"

class InputSystem :	public System {
public:
	InputSystem();
	~InputSystem();
	void process(ComponentBag bag, float dt);

	float getMouseIntensity();
	void setMouseIntensity(float intensity);

private:
	float m_MouseIntensity;

};

