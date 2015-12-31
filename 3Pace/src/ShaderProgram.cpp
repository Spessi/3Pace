#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) {
	m_ProgramID = glCreateProgram();
	for (GLuint i = 0; i < shaders.size(); ++i) {
		glAttachShader(m_ProgramID, shaders[i].getShaderID());
	}

	glLinkProgram(m_ProgramID);

	for (GLuint i = 0; i < shaders.size(); ++i) {
		glDetachShader(m_ProgramID, shaders[i].getShaderID());
		glDeleteShader(shaders[i].getShaderID());
	}
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(m_ProgramID);
}

const GLuint ShaderProgram::getProgramID() const {
	return m_ProgramID;
}