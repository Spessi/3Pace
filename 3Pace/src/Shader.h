#pragma once

#include <fstream>
#include <string>
#include <gl/glew.h>
#include <SDL_opengl.h>


class Shader {
public:
	Shader();
	~Shader();
	bool load(const std::string& path, GLenum shaderType);
	const GLuint getShaderID() const;

private:
	GLuint m_ShaderID;
	std::string loadFromFile(const std::string& path);
};

