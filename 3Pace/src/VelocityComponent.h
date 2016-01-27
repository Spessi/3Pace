#pragma once

#include "Component.h"
#include "glm/glm.hpp"


class VelocityComponent : public Component {
public:
	VelocityComponent();
	VelocityComponent(float velo);
	~VelocityComponent();
	ComponentBitID getID();

	float getVelocity();
	void setVelocity(float velocity);
private:
	float m_Velocity;
};

