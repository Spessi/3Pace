#pragma once

#include "Component.h"
#include <map>

class IntentComponent : public Component {
public:
	IntentComponent();
	~IntentComponent();
	ComponentBitID getID();

	bool getMoveForward();
	void setMoveForward(bool state);

	bool getMoveBackward();
	void setMoveBackward(bool state);

	bool getMoveLeft();
	void setMoveLeft(bool state);

	bool getMoveRight();
	void setMoveRight(bool state);

	float getRotateHorizontalDelta();
	void setRotateHorizontalDelta(float dx);

	float getRotateVerticalDelta();
	void setRotateVerticalDelta(float dy);

private:
	bool m_MoveForward;
	bool m_MoveBackward;
	bool m_MoveLeft;
	bool m_MoveRight;
	float m_RotateHorizontalDelta;
	float m_RotateVerticalDelta;
};

