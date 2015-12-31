#include "Camera.h"
#include <iostream>


Camera::Camera() : m_Position(0.0f, 0.0f, 0.0f), m_HorizontalAngle(0.0f), m_VerticalAngle(0.0f) {

}

Camera::Camera(glm::vec3 pos, GLfloat horiAngle, GLfloat vertAngle, GLboolean constrainVertical, GLfloat movementSpeed, GLfloat mouseIntensity) {
	m_Position = pos;
	m_HorizontalAngle = horiAngle;
	m_VerticalAngle = vertAngle;
	m_ConstrainVertical = constrainVertical;
	m_MovementSpeed = movementSpeed;
	m_MouseIntensity = mouseIntensity;
}

void Camera::processKeyboard(SDL_Keycode key, GLfloat dt) {
	GLfloat speed = m_MovementSpeed * dt;
	
	if (key == SDLK_w || key == SDLK_UP)
		m_Position += getFrontVector() * speed;

	if(key == SDLK_s || key == SDLK_DOWN)
		m_Position -= getFrontVector() * speed;

	if (key == SDLK_a || key == SDLK_LEFT)
		m_Position -= getRightVector() * speed;

	if (key == SDLK_d || key == SDLK_RIGHT)
		m_Position += getRightVector() * speed;
}

void Camera::processMouse(int dx, int dy, GLfloat dt) {
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

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_Position, m_Position + getFrontVector(), getUpVector());
}

Camera::~Camera() {
}
