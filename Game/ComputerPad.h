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
	CVector3	GetPosition() { return CVector3::Zero(); };
	CQuaternion GetRotation() { return m_rot; };
	/*void SetPad(GamePad* gamePad)
	{
		m_gamePad = gamePad;
	}*/
	void UpdatePad();
private:
	/*GamePad* m_gamePad = nullptr;*/
	float m_stickL = 0.0f;
	bool m_pressAccel = false;
	bool m_pressJump = false;
	CQuaternion m_rot = CQuaternion::Identity();
};

