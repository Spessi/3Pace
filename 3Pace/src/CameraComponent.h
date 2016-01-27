#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class CameraComponent :	public Component {
public:
	CameraComponent(std::uint32_t targetEntityID = 0);
	~CameraComponent();

	ComponentBitID getID();

	std::uint32_t getTargetEntity();
	void setTargetEntity(std::uint32_t id);
	
	float getNearClip();
	void setNearClip(float nearClip);

	float getFarClip();
	void setFarClip(float farClip);

	float getAspectRatio();
	void setAspectRatio(float aspect);

	glm::mat4 getProjectionMatrix();
	void setProjectionMatrix(glm::mat4 projMat);

	glm::mat4 getViewMatrix();
	void setViewMatrix(glm::mat4 viewMat);

private:
	std::uint32_t m_TargetEntity;
	float m_NearClip;
	float m_FarClip;
	float m_AspectRatio;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
};

