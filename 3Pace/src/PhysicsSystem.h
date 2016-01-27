#pragma once

#include <memory>
#include "System.h"
#include "Component.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "IntentComponent.h"

#include "SDLHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PhysicsSystem : public System {
public:
	PhysicsSystem();
	~PhysicsSystem();
	void process(ComponentBag bag, float dt);
};

