#include "MeshComponent.h"

MeshComponent::MeshComponent(GLuint vao, GLuint verticesCount) {
	m_VAO = vao;
	m_VerticesCount = verticesCount;
	m_Color = glm::vec3(0.46f, 0.32f, 0.2f);
}


MeshComponent::~MeshComponent() {
}

ComponentBitID MeshComponent::getID() {
	return bittify(Component::Types::MESH);
}

GLuint MeshComponent::getVAO() {
	return m_VAO;
}

GLuint MeshComponent::getVerticesCount() {
	return m_VerticesCount;
}

glm::vec3 MeshComponent::getColor() {
	return m_Color;
}

void MeshComponent::setColor(glm::vec3 color) {
	m_Color = color;
}