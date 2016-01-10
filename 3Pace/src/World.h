#pragma once

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "SDLHelper.h"
#include "Heightmap.h"

class World {
public:
	World();
	~World();
	bool init();
	void process(GLfloat delta);
	void render();
	const ShaderProgram* getShaderProg() const;
	Camera* getCamera();

private:
	ShaderProgram* m_ShaderProg;
	Camera* m_Camera;
	Heightmap m_Heightmap;

	GLfloat m_Delta;
	GLboolean m_DrawWireframe;
};

