#include "IntentComponent.h"


IntentComponent::IntentComponent() {
	m_MoveForward = false;
	m_MoveBackward = false;
	m_MoveLeft = false;
	m_MoveRight = false;
	m_RotateHorizontalDelta = 0.0f;
	m_RotateVerticalDelta = 0.0f;
}


IntentComponent::~IntentComponent() {
}

ComponentBitID IntentComponent::getID() {
	return bittify(Component::Types::INTENT);
}

bool IntentComponent::getMoveForward() {
	return m_MoveForward;
}
void IntentComponent::setMoveForward(bool state) {
	m_MoveForward = state;
}

bool IntentComponent::getMoveBackward() {
	return m_MoveBackward;
}
void IntentComponent::setMoveBackward(bool state) {
	m_MoveBackward = state;
}

bool IntentComponent::getMoveLeft() {
	return m_MoveLeft;
}
void IntentComponent::setMoveLeft(bool state) {
	m_MoveLeft = state;
}

bool IntentComponent::getMoveRight() {
	return m_MoveRight;
}
void IntentComponent::setMoveRight(bool state) {
	m_MoveRight = state;
}


/* Rotate */
float IntentComponent::getRotateHorizontalDelta() {
	return m_RotateHorizontalDelta;
}
void IntentComponent::setRotateHorizontalDelta(float dx) {
	m_RotateHorizontalDelta = dx;
}

float IntentComponent::getRotateVerticalDelta() {
	return m_RotateVerticalDelta;
}
void IntentComponent::setRotateVerticalDelta(float dy) {
	m_RotateVerticalDelta = dy;
}