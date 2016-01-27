#include "VelocityComponent.h"

VelocityComponent::VelocityComponent() {
	m_Velocity = 0.0f;
}

VelocityComponent::VelocityComponent(float velo) : VelocityComponent() {
	m_Velocity = velo;
}

VelocityComponent::~VelocityComponent() {
}

ComponentBitID VelocityComponent::getID() {
	return bittify(Component::Types::VELOCITY);
}

float VelocityComponent::getVelocity() {
	return m_Velocity;
}

void VelocityComponent::setVelocity(float velocity) {
	m_Velocity = velocity;
}