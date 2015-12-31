#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>
#include <vector>
#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram(const std::vector<Shader>& shaders);
	~ShaderProgram();
	const GLuint getProgramID() const;
private:
	GLuint m_ProgramID;
};

