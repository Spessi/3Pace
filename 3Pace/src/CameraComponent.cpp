#include "CameraComponent.h"



CameraComponent::CameraComponent(std::uint32_t targetEntityID) {
	m_TargetEntity = targetEntityID;
	m_NearClip = 0.1f;
	m_FarClip = 1000.0f;
	m_AspectRatio = 16.0f/9.0f;
	m_ProjectionMatrix = glm::mat4();
	m_ViewMatrix = glm::mat4();
}


CameraComponent::~CameraComponent() {
}

ComponentBitID CameraComponent::getID() {
	return Component::bittify(Component::Types::CAMERA);
}

std::uint32_t CameraComponent::getTargetEntity() {
	return m_TargetEntity;
}

void CameraComponent::setTargetEntity(std::uint32_t id) {
	m_TargetEntity = id;
}

float CameraComponent::getNearClip() {
	return m_NearClip;
}
void CameraComponent::setNearClip(float nearClip) {
	m_NearClip = nearClip;
}

float CameraComponent::getFarClip() {
	return m_FarClip;
}
void CameraComponent::setFarClip(float farClip) {
	m_FarClip = farClip;
}

float CameraComponent::getAspectRatio() {
	return m_AspectRatio;
}
void CameraComponent::setAspectRatio(float aspect) {
	m_AspectRatio = aspect;
}

glm::mat4 CameraComponent::getProjectionMatrix() {
	return m_ProjectionMatrix;
}
void CameraComponent::setProjectionMatrix(glm::mat4 projMat) {
	m_ProjectionMatrix = projMat;
}

glm::mat4 CameraComponent::getViewMatrix() {
	return m_ViewMatrix;
}
void CameraComponent::setViewMatrix(glm::mat4 viewMat) {
	m_ViewMatrix = viewMat;
}