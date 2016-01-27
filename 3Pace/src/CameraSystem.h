#pragma once

#include "System.h"
#include "CameraComponent.h"
#include "PositionComponent.h"
#include "EntityManager.h"
#include "SDLHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraSystem : public System {
public:
	CameraSystem(EntityManager* entityMgr);
	~CameraSystem();
	void process(ComponentBag bag, float dt);

	const std::shared_ptr<CameraComponent> getActiveCamera() const;
	void setActiveCamera(CameraComponent* camera);

private:
	std::shared_ptr<EntityManager> m_EntityManager;
	std::shared_ptr<CameraComponent> m_ActiveCamera;
};

