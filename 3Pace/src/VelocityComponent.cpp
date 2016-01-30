#include "VelocityComponent.h"

VelocityComponent::VelocityComponent() {
	m_moveSpeed = 0.0f;
	m_moveSpeedMax = 0.0f;
	m_rotationSpeed = 0.0f;
	m_rotationSpeedMax = 0.0f;
	m_upwardSpeed = 0.0f;
}

VelocityComponent::VelocityComponent(float moveMax, float rotationMax) : VelocityComponent() {
	m_moveSpeedMax = moveMax;
	m_rotationSpeedMax = rotationMax;
}

VelocityComponent::~VelocityComponent() {
}

ComponentBitID VelocityComponent::getID() {
	return bittify(Component::Types::VELOCITY);
}

float VelocityComponent::getMoveSpeed() {
	return m_moveSpeed;
}

void VelocityComponent::setMoveSpeed(float velocity) {
	m_moveSpeed = velocity;
}

float VelocityComponent::getMoveSpeedMax() {
	return m_moveSpeedMax;
}


float VelocityComponent::getRotationSpeed() {
	return m_rotationSpeed;
}

void VelocityComponent::setRotationSpeed(float velocity) {
	m_rotationSpeed = velocity;
}

float VelocityComponent::getRotationSpeedMax() {
	return m_rotationSpeedMax;
}


float VelocityComponent::getUpwardSpeed() {
	return m_upwardSpeed;
}

void VelocityComponent::setUpwardSpeed(float velocity) {
	m_upwardSpeed = velocity;
}