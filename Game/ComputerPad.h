#pragma once
#include "GamePad.h"
class ComputerPad : public GamePad
{
public:
	ComputerPad();
	~ComputerPad();
	float GetLstickXF()
	{
		return m_stickL;
	}
	bool  IsPressAccel()
	{
		return m_pressAccel;
	}
	bool  IsPressJump()
	{
		return m_pressJump;
	}
	void UpdatePad();
private:
	float m_stickL = 0.0f;
	bool m_pressAccel = false;
	bool m_pressJump = false;
};

