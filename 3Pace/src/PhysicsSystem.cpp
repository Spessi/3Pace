#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {
	this->registerComponent(Component::Types::POSITION);
	this->registerComponent(Component::Types::VELOCITY);
	this->registerComponent(Component::Types::INTENT);
}


PhysicsSystem::~PhysicsSystem() {
}

void PhysicsSystem::process(ComponentBag bag, float dt) {
	// Check if System needs to interact with the current ComponentBag
	if (componentCheck(bag) == false)
		return;

	// Get references to the Components
	std::shared_ptr<PositionComponent> posComp = std::dynamic_pointer_cast<PositionComponent>(getComponentFromBag(bag, Component::Types::POSITION));
	std::shared_ptr<VelocityComponent> veloComp = std::dynamic_pointer_cast<VelocityComponent>(getComponentFromBag(bag, Component::Types::VELOCITY));
	std::shared_ptr<IntentComponent> intentComp = std::dynamic_pointer_cast<IntentComponent>(getComponentFromBag(bag, Component::Types::INTENT));

	// Increment velocity (-> Accelerate)
	if (intentComp->getMoveForward()) {
		std::cout << "FrontVec Z: " << posComp->getFrontVector().z << std::endl;
		posComp->setPosition(posComp->getPosition() + veloComp->getVelocity() * glm::normalize(posComp->getFrontVector()) * dt);
	}	
	if (intentComp->getMoveBackward()) {
		posComp->setPosition(posComp->getPosition() - veloComp->getVelocity() * glm::normalize(posComp->getFrontVector()) * dt);
	}
	if (intentComp->getMoveLeft()) {
		posComp->setPosition(posComp->getPosition() - veloComp->getVelocity() / 2.0f * glm::normalize(posComp->getRightVector()) * dt);
	}
	if (intentComp->getMoveRight()) {
		posComp->setPosition(posComp->getPosition() + veloComp->getVelocity() / 2.0f * glm::normalize(posComp->getRightVector()) * dt);
	}

	
	posComp->setHorizontalAngle(posComp->getHorizontalAngle() - intentComp->getRotateHorizontalDelta());
	posComp->setVerticalAngle(posComp->getVerticalAngle() + intentComp->getRotateVerticalDelta());

	glm::vec3 frontVec = 
		glm::vec3(
			cos(glm::radians(posComp->getVerticalAngle())) * sin(glm::pi<float>() + glm::radians(posComp->getHorizontalAngle())),
			sin(glm::radians(posComp->getVerticalAngle())),
			cos(glm::radians(posComp->getVerticalAngle())) * cos(glm::pi<float>() + glm::radians(posComp->getHorizontalAngle()))
		);
	posComp->setFrontVector(frontVec);

	glm::vec3 rightVec = 
		glm::vec3(
			cos(glm::radians(-posComp->getHorizontalAngle())),
			0,
			sin(glm::radians(-posComp->getHorizontalAngle()))
		);

	posComp->setRightVector(rightVec);
}
