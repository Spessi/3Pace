#include "InputSystem.h"



InputSystem::InputSystem() {
	this->registerComponent(Component::Types::INTENT);
	m_MouseIntensity = 4.0f;
}


InputSystem::~InputSystem() {
}

float InputSystem::getMouseIntensity() {
	return m_MouseIntensity;
}
void InputSystem::setMouseIntensity(float intensity) {
	m_MouseIntensity = intensity;
}

void InputSystem::process(ComponentBag bag, float dt) {
	if (componentCheck(bag) == false)
		return;

	std::shared_ptr<IntentComponent> intentComp = std::dynamic_pointer_cast<IntentComponent>(getComponentFromBag(bag, Component::Types::INTENT));
	
	// Get keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// Get mouse state
	int dx, dy;
	Uint32 mouseState = SDL_GetRelativeMouseState(&dx, &dy);


	
	// Handle Mouse Input
	if(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		intentComp->setRotateHorizontalDelta(m_MouseIntensity * dt * (float)dx);
	}
	else {
		intentComp->setRotateHorizontalDelta(0.0f);
	}

	if ((mouseState & (SDL_BUTTON(SDL_BUTTON_LEFT) | SDL_BUTTON(SDL_BUTTON_RIGHT))) == 5)
		intentComp->setMoveForward(true);
	else
		intentComp->setMoveForward(state[SDL_SCANCODE_W]);

	intentComp->setMoveBackward(state[SDL_SCANCODE_S]);
	intentComp->setTurnLeft(state[SDL_SCANCODE_A]);
	intentComp->setTurnRight(state[SDL_SCANCODE_D]);
	intentComp->setJump(state[SDL_SCANCODE_SPACE]);
}