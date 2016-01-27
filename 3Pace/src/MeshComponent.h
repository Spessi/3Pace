#pragma once

#include "Component.h"
#include "SDLHelper.h"


class MeshComponent : public Component {
public:
	MeshComponent(GLuint vao, GLuint verticesCount);
	~MeshComponent();
	ComponentBitID getID();
	GLuint getVAO();
	GLuint getVerticesCount();

	glm::vec3 getColor();
	void setColor(glm::vec3 color);

private:
	GLuint m_VAO;
	GLuint m_VerticesCount;
	glm::vec3 m_Color;
};

