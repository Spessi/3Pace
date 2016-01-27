#pragma once

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "ShaderProgram.h"
#include "SDLHelper.h"
#include "Heightmap.h"

#include "EntityManager.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CameraComponent.h"
#include "PhysicsSystem.h"
#include "CameraSystem.h"
#include "SystemManager.h"
#include "RenderSystem.h"
#include "MeshComponent.h"
#include "InputSystem.h"
#include "IntentComponent.h"

class World {
public:
	World();
	~World();
	bool init();
	void process(GLfloat delta);
	void render();
	const ShaderProgram* getShaderProg() const;

private:
	ShaderProgram* m_ShaderProg;
	Heightmap m_Heightmap;
	EntityManager* m_EntityMgr;
	SystemManager* m_SystemMgr;
	CameraSystem* m_CameraSystem;

	GLfloat m_Delta;
	GLboolean m_DrawWireframe;

	GLuint loadCube();
};

