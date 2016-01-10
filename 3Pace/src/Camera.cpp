#include "Camera.h"
#include <iostream>


Camera::Camera() {

}

Camera::~Camera() {
}

bool Camera::init(glm::vec3 pos, GLfloat horiAngle, GLfloat vertAngle, GLfloat nearclip, GLfloat farclip, GLfloat ratio, GLboolean constrainVertical, GLfloat movementSpeed, GLfloat mouseIntensity) {
	m_Position = pos;
	m_HorizontalAngle = horiAngle;
	m_VerticalAngle = vertAngle;
	m_FarClip = farclip;
	m_NearClip = nearclip;
	m_AspectRatio = ratio;

	m_ConstrainVertical = constrainVertical;
	m_MovementSpeed = movementSpeed;
	m_MouseIntensity = mouseIntensity;

	return true;
}

void Camera::setAspectRatio(GLfloat ratio) {
	if(ratio > 0.0f)
		m_AspectRatio = ratio;
}

void Camera::processKeyboard(GLfloat dt) {
	GLfloat speed = m_MovementSpeed * dt;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
		m_Position += getFrontVector() * speed;

	if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
		m_Position -= getFrontVector() * speed;

	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
		m_Position -= getRightVector() * speed;

	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
		m_Position += getRightVector() * speed;

	if (state[SDL_SCANCODE_SPACE])
		m_Position += getUpVector() * speed;
}

void Camera::processMouse(GLfloat dt) {
	int dx, dy;
	SDL_GetRelativeMouseState(&dx, &dy);

	GLfloat intensity = m_MouseIntensity * dt;

	m_HorizontalAngle -= (GLfloat)dx * intensity;
	m_VerticalAngle -= (GLfloat)dy * intensity;

	if (m_HorizontalAngle >= 360.0f)
		m_HorizontalAngle = 0.0f;

	if (m_ConstrainVertical) {
		if (m_VerticalAngle >= 89.0f)
			m_VerticalAngle = 89.0f;
		else if (m_VerticalAngle <= -89.0f)
			m_VerticalAngle = -89.0f;
	}
}

const GLfloat Camera::getHorizontalAngle() const {
	return m_HorizontalAngle;
}

const GLfloat Camera::getVerticalAngle() const {
	return m_VerticalAngle;
}

glm::vec3 Camera::getFrontVector() const {
	return glm::vec3(cos(glm::radians(m_VerticalAngle)) * sin(glm::radians(m_HorizontalAngle)), sin(glm::radians(m_VerticalAngle)), cos(glm::radians(m_VerticalAngle)) * cos(glm::radians(m_HorizontalAngle)));
}

glm::vec3 Camera::getRightVector() const {
	return glm::vec3(sin(glm::radians(m_HorizontalAngle) - glm::half_pi<GLfloat>()), 0, cos(glm::radians(m_HorizontalAngle) - glm::half_pi<GLfloat>()));
}

glm::vec3 Camera::getUpVector() const {
	return glm::cross(getRightVector(), getFrontVector());
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspective(glm::radians(45.0f), m_AspectRatio, m_NearClip, m_FarClip);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_Position, m_Position + getFrontVector(), getUpVector());
}
