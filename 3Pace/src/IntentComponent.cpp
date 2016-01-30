#include "IntentComponent.h"


IntentComponent::IntentComponent() {
	m_MoveForward = false;
	m_MoveBackward = false;
	m_TurnLeft = false;
	m_TurnRight = false;
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

bool IntentComponent::getTurnLeft() {
	return m_TurnLeft;
}
void IntentComponent::setTurnLeft(bool state) {
	m_TurnLeft = state;
}

bool IntentComponent::getTurnRight() {
	return m_TurnRight;
}
void IntentComponent::setTurnRight(bool state) {
	m_TurnRight = state;
}

bool IntentComponent::getJump() {
	return m_Jump;
}
void IntentComponent::setJump(bool state) {
	m_Jump = state;
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