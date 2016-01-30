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

	bool getTurnLeft();
	void setTurnLeft(bool state);

	bool getTurnRight();
	void setTurnRight(bool state);

	bool getJump();
	void setJump(bool state);

	float getRotateHorizontalDelta();
	void setRotateHorizontalDelta(float dx);

	float getRotateVerticalDelta();
	void setRotateVerticalDelta(float dy);

private:
	bool m_MoveForward;
	bool m_MoveBackward;
	bool m_TurnLeft;
	bool m_TurnRight;
	bool m_Jump;
	float m_RotateHorizontalDelta;
	float m_RotateVerticalDelta;
};

