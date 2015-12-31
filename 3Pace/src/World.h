#pragma once

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "SDLHelper.h"

class World {
public:
	World();
	~World();
	void processKeyboard(SDL_Keycode key);
	void process(GLfloat delta);
	void render();
	const ShaderProgram* getShaderProg() const;
	void setProjectionMatrix(glm::mat4 mat);

private:
	ShaderProgram* m_ShaderProg;
	Camera* m_Camera;
	glm::mat4 m_ProjectionMatrix;
	GLfloat m_Delta;

	// Test
	float m_Angle = 0.0f, m_Angle2 = 0;
	void loadCube();
};

