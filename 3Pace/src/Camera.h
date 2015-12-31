#pragma once

#include "SDLHelper.h"
#include <glm/glm.hpp>
#include <SDL_opengl.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	enum Direction {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	Camera();
	Camera(glm::vec3 pos, GLfloat horiAngle, GLfloat vertAngle, GLboolean constrainVertical, GLfloat movementSpeed, GLfloat mouseIntensity);
	~Camera();
	glm::mat4 getViewMatrix() const;
	void processKeyboard(SDL_Keycode key, GLfloat dt);
	void processMouse(int dx, int dy, GLfloat dt);

	const GLfloat getHorizontalAngle() const;
	const GLfloat getVerticalAngle() const;

private:
	glm::vec3 m_Position;
	GLfloat m_HorizontalAngle;
	GLfloat m_VerticalAngle;
	GLboolean m_ConstrainVertical;
	GLfloat m_MovementSpeed;
	GLfloat m_MouseIntensity;

	glm::vec3 getFrontVector() const;
	glm::vec3 getRightVector() const;
	glm::vec3 getUpVector() const;
};

