#include "RenderSystem.h"



RenderSystem::RenderSystem(CameraSystem* camSys, ShaderProgram* shaderProg) {
	m_CameraSystem = camSys;
	m_ShaderProg = shaderProg;

	this->registerComponent(Component::Types::MESH);
	this->registerComponent(Component::Types::POSITION);
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::process(ComponentBag bag, float dt) {
	glm::mat4 modelMatrix;

	if (componentCheck(bag) == false)
		return;

	if (m_CameraSystem->getActiveCamera() == nullptr)
		return;

	// Get references to the Components
	std::shared_ptr<MeshComponent> meshComp = std::dynamic_pointer_cast<MeshComponent>(getComponentFromBag(bag, Component::Types::MESH));
	std::shared_ptr<PositionComponent> posComp = std::dynamic_pointer_cast<PositionComponent>(getComponentFromBag(bag, Component::Types::POSITION));


	// bind the program (the shaders)
	glUseProgram(m_ShaderProg->getProgramID());

	// Get the projection and modelview location id from the shader program
	GLuint projectionLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "projection");
	GLuint modelviewLoc = glGetUniformLocation(m_ShaderProg->getProgramID(), "modelview");


	// Transform light position (0/100/0) into ModelView space
	glm::vec3 lightPos = glm::vec3(m_CameraSystem->getActiveCamera()->getViewMatrix() * modelMatrix * glm::vec4(0.0f, 100.0f, 0.0f, 1.0f));
	glUniform3fv(m_ShaderProg->getUniformLoc("lightPos"), 1, glm::value_ptr(lightPos));

	// Set projection matrix in shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_CameraSystem->getActiveCamera()->getProjectionMatrix()));

	// Set the Model View Matrix for the renderable Entity
	modelMatrix = glm::translate(glm::mat4(), posComp->getPosition());
	modelMatrix = glm::rotate(modelMatrix, glm::radians(posComp->getHorizontalAngle()), glm::vec3(0.0f, 1.0f, 0.0f));

	// Set ModelView matrix in shader
	glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, glm::value_ptr(m_CameraSystem->getActiveCamera()->getViewMatrix() * modelMatrix));

	// Set mesh color
	glUniform3fv(m_ShaderProg->getUniformLoc("objectColor"), 1, glm::value_ptr(meshComp->getColor()));

	glBindVertexArray(meshComp->getVAO());
	glDrawElements(GL_TRIANGLES, meshComp->getVerticesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}