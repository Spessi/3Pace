#pragma once

#include <fstream>
#include <string>
#include <gl/glew.h>
#include <SDL_opengl.h>


class Shader {
public:
	Shader(const std::string& path, GLenum shaderType);
	~Shader();
	const GLuint getShaderID() const;

private:
	GLuint m_ShaderID;
	std::string loadFromFile(const std::string& path);
};

