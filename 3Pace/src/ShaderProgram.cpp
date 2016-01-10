#include "ShaderProgram.h"



ShaderProgram::ShaderProgram() {

}

ShaderProgram::~ShaderProgram() {
}

bool ShaderProgram::compileProgram(const std::vector<Shader>& shaders) {
	m_ProgramID = glCreateProgram();
	for (GLuint i = 0; i < shaders.size(); ++i) {
		glAttachShader(m_ProgramID, shaders[i].getShaderID());
	}

	glLinkProgram(m_ProgramID);

	for (GLuint i = 0; i < shaders.size(); ++i) {
		glDetachShader(m_ProgramID, shaders[i].getShaderID());
		glDeleteShader(shaders[i].getShaderID());
	}

	return true;
}

void ShaderProgram::deleteProgram() {
	glDeleteProgram(m_ProgramID);
}


GLuint ShaderProgram::getUniformLoc(std::string name) {
	return glGetUniformLocation(m_ProgramID, name.c_str());
}


const GLuint ShaderProgram::getProgramID() const {
	return m_ProgramID;
}