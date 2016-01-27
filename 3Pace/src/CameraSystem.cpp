#include "CameraSystem.h"


CameraSystem::CameraSystem(EntityManager* entityMgr) {
	m_EntityManager = std::shared_ptr<EntityManager>(entityMgr);

	this->registerComponent(Component::Types::POSITION);
	this->registerComponent(Component::Types::CAMERA);

	m_ActiveCamera = nullptr;
}

CameraSystem::~CameraSystem() {
}

void CameraSystem::process(ComponentBag bag, float dt) {
	if (componentCheck(bag) == false)
		return;

	std::shared_ptr<PositionComponent> posComp = std::dynamic_pointer_cast<PositionComponent>(getComponentFromBag(bag, Component::Types::POSITION));
	std::shared_ptr<CameraComponent> camComp = std::dynamic_pointer_cast<CameraComponent>(getComponentFromBag(bag, Component::Types::CAMERA));

	if (m_ActiveCamera == nullptr)
		m_ActiveCamera = camComp;

	// Calculate projection matrix
	camComp->setProjectionMatrix(glm::perspective(glm::radians(45.0f), camComp->getAspectRatio(), camComp->getNearClip(), camComp->getFarClip()));

	// Check if the camera has a target entity
	if (camComp->getTargetEntity() > 0) {
		// If it has a target entity, place the camera behind it (3rd person perspective)
		ComponentBag targetBag = m_EntityManager->getEntity(camComp->getTargetEntity());
		std::shared_ptr<PositionComponent> targetPosComp = std::dynamic_pointer_cast<PositionComponent>(getComponentFromBag(targetBag, Component::Types::POSITION));
		
		posComp->setPosition(targetPosComp->getPosition() - 15.0f * targetPosComp->getFrontVector() + glm::vec3(0.0f, 3.0f, 0.0f));
		camComp->setViewMatrix(glm::lookAt(posComp->getPosition(), targetPosComp->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	else {
		// If it has no target entity, use the camera entities' position
		//camComp->setViewMatrix(glm::lookAt(posComp->getPosition(), posComp->getPosition() + posComp->getFrontVector(), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
}

void CameraSystem::setActiveCamera(CameraComponent* camera) {
	m_ActiveCamera = std::shared_ptr<CameraComponent>(camera);
}

const std::shared_ptr<CameraComponent> CameraSystem::getActiveCamera() const {
	return m_ActiveCamera;
}