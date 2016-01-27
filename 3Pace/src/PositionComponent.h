#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class PositionComponent : public Component {
public:
	PositionComponent();
	PositionComponent(glm::vec3 position);
	~PositionComponent();
	ComponentBitID getID();
	
	glm::vec3 getFrontVector();
	glm::vec3 getRightVector();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	float getHorizontalAngle();
	float getVerticalAngle();

	void setFrontVector(glm::vec3 direction);
	void setRightVector(glm::vec3 direction);
	void setPosition(glm::vec3 pos);
	void setScale(glm::vec3 sca);
	void setHorizontalAngle(float angle);
	void setVerticalAngle(float angle);
	

private:
	glm::vec3 m_FrontVector;
	glm::vec3 m_RightVector;
	glm::vec3 m_Position;
	float m_HorizontalAngle;
	float m_VerticalAngle;
	glm::vec3 m_Scale;
};

