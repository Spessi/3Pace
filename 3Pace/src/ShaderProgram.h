#pragma once

#include <gl/glew.h>
#include <SDL_opengl.h>
#include <vector>
#include "Shader.h"

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();
	bool compileProgram(const std::vector<Shader>& shaders);
	void deleteProgram();
	GLuint getUniformLoc(std::string name);
	const GLuint getProgramID() const;
private:
	GLuint m_ProgramID;
};

