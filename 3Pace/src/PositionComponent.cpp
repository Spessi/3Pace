#include "PositionComponent.h"



PositionComponent::PositionComponent() {
	m_Position = glm::vec3(0, 0, 0);
	m_Scale = glm::vec3(1, 1, 1);

	// Default direction is towards the -z axis
	m_FrontVector = glm::vec3(0.0f, 0.0f, -1.0f);
	m_RightVector = glm::vec3(1.0f, 0.0f, 0.0f);


	m_HorizontalAngle = 0.0;
	m_VerticalAngle = 0.0f;
}

PositionComponent::PositionComponent(glm::vec3 position) : PositionComponent() {
	m_Position = position;
}


PositionComponent::~PositionComponent() {
	std::cout << "PositionComponent::~PositionComponent" << std::endl;
}

ComponentBitID PositionComponent::getID() {
	return bittify(Component::Types::POSITION);
}

glm::vec3 PositionComponent::getFrontVector() {
	return m_FrontVector;
}
glm::vec3 PositionComponent::getRightVector() {
	return m_RightVector;
}

glm::vec3 PositionComponent::getPosition() {
	return m_Position;
}
float PositionComponent::getHorizontalAngle() {
	return m_HorizontalAngle;
}
float PositionComponent::getVerticalAngle() {
	return m_VerticalAngle;
}
glm::vec3 PositionComponent::getScale() {
	return m_Scale;
}

void PositionComponent::setFrontVector(glm::vec3 direction) {
	m_FrontVector = direction;
}
void PositionComponent::setRightVector(glm::vec3 direction) {
	m_RightVector = direction;
}
void PositionComponent::setPosition(glm::vec3 pos) {
	m_Position = pos;
}
void PositionComponent::setHorizontalAngle(float angle) {
	m_HorizontalAngle = angle;
}
void PositionComponent::setVerticalAngle(float angle) {
	m_VerticalAngle = angle;
}
void PositionComponent::setScale(glm::vec3 sca) {
	m_Scale = sca;
}