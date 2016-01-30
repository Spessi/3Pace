#pragma once

#include "Component.h"
#include "glm/glm.hpp"


class VelocityComponent : public Component {
public:
	VelocityComponent();
	VelocityComponent(float moveMax, float rotationMax);
	~VelocityComponent();
	ComponentBitID getID();

	float getMoveSpeed();
	void setMoveSpeed(float velocity);
	float getMoveSpeedMax();

	float getRotationSpeed();
	void setRotationSpeed(float velocity);
	float getRotationSpeedMax();

	float getUpwardSpeed();
	void setUpwardSpeed(float velocity);

private:
	float m_moveSpeed;
	float m_moveSpeedMax;
	float m_rotationSpeed;
	float m_rotationSpeedMax;
	float m_upwardSpeed;
};

