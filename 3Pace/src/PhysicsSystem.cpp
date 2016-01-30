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

	// Process Input Intentions
	if (intentComp->getMoveForward())
		veloComp->setMoveSpeed(veloComp->getMoveSpeedMax());
	else if (intentComp->getMoveBackward())
		veloComp->setMoveSpeed(-veloComp->getMoveSpeedMax());
	else
		veloComp->setMoveSpeed(0);

	veloComp->setRotationSpeed(0);

	if (intentComp->getTurnLeft())
		veloComp->setRotationSpeed(veloComp->getRotationSpeedMax());
	if (intentComp->getTurnRight())
		veloComp->setRotationSpeed(-veloComp->getRotationSpeedMax());
	std::cout << "TurnLeft: " << intentComp->getTurnLeft() << " | TurnRight: " << intentComp->getTurnRight() << " | RotSpeed: " << veloComp->getRotationSpeed() << std::endl;


	if (intentComp->getJump() && !posComp->getIsInAir()) {
		veloComp->setUpwardSpeed(200);
		posComp->setIsInAir(true);
	}

	// Process Gravity
	veloComp->setUpwardSpeed(veloComp->getUpwardSpeed() + (-500.0f) * dt);

	// Rotation
	posComp->setHorizontalAngle(posComp->getHorizontalAngle() + veloComp->getRotationSpeed() * dt);

	// Forward movement
	float distance = veloComp->getMoveSpeed() * dt;
	float dx = distance * glm::sin(glm::pi<float>() + glm::radians(posComp->getHorizontalAngle()));
	float dz = distance * glm::cos(glm::pi<float>() + glm::radians(posComp->getHorizontalAngle()));
	float dy = veloComp->getUpwardSpeed() * dt;
	glm::vec3 deltaVec = glm::vec3(dx, dy, dz);
	posComp->setPosition(posComp->getPosition() + deltaVec);

	if (posComp->getPosition().y <= 30.0f) {
		veloComp->setUpwardSpeed(0.0f);
		posComp->setPosition(glm::vec3(posComp->getPosition().x, 30.0f, posComp->getPosition().z));
		posComp->setIsInAir(false);
	}


	/*
	// Increment velocity (-> Accelerate)
	if (intentComp->getMoveForward()) {
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

	posComp->setRightVector(rightVec);*/
}
