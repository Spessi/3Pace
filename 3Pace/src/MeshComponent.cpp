#include "MeshComponent.h"

MeshComponent::MeshComponent(GLuint vao, GLuint verticesCount, glm::vec3 color) {
	m_VAO = vao;
	m_VerticesCount = verticesCount;
	m_Color = color;
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