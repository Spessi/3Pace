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
	~Camera();
	bool init(glm::vec3 pos, GLfloat horiAngle, GLfloat vertAngle, GLfloat nearclip, GLfloat farclip, GLfloat ratio, GLboolean constrainVertical = true, GLfloat movementSpeed = 1.0f, GLfloat mouseIntensity = 1.0f);
	void setAspectRatio(GLfloat ratio);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix() const;
	const GLfloat getHorizontalAngle() const;
	const GLfloat getVerticalAngle() const;
	void processKeyboard(GLfloat dt);
	void processMouse(GLfloat dt);


private:
	glm::vec3 m_Position;
	GLfloat m_HorizontalAngle;
	GLfloat m_VerticalAngle;
	GLfloat m_FarClip;
	GLfloat m_NearClip;
	GLfloat m_AspectRatio;
	GLboolean m_ConstrainVertical;
	GLfloat m_MovementSpeed;
	GLfloat m_MouseIntensity;

	glm::vec3 getFrontVector() const;
	glm::vec3 getRightVector() const;
	glm::vec3 getUpVector() const;
};

