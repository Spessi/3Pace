#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "System.h"
#include "MeshComponent.h"
#include "PositionComponent.h"
#include "ShaderProgram.h"
#include "CameraSystem.h"

class RenderSystem : public System {
public:
	RenderSystem(CameraSystem* camSys, ShaderProgram* shaderProg);
	~RenderSystem();
	void process(ComponentBag bag, float dt);

private:
	ShaderProgram* m_ShaderProg;
	CameraSystem* m_CameraSystem;
};

