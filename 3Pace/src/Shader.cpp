#include "Shader.h"


Shader::Shader() {
}

Shader::~Shader() {
}

bool Shader::load(const std::string& path, GLenum shaderType) {
	std::string shaderCode = loadFromFile(path);

	m_ShaderID = glCreateShader(shaderType);
	if (m_ShaderID == 0)
		throw std::runtime_error("Couldn't create shader!");

	const GLchar* vertexSourcePointer = shaderCode.c_str();
	glShaderSource(m_ShaderID, 1, &vertexSourcePointer, 0);
	glCompileShader(m_ShaderID);

	return true;
}

const GLuint Shader::getShaderID() const {
	return m_ShaderID;
}

std::string Shader::loadFromFile(const std::string& path) {
	std::string shaderCode;
	std::ifstream inStream(path, std::ios::in);
	std::string line = "";

	if (!inStream.is_open())
		return ""; // todo: error handling

	while (getline(inStream, line))
		shaderCode += line + '\n';

	return shaderCode;
}