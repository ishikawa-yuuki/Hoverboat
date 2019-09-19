#pragma once
#include "character/CharacterController.h"
class PlayerMove 
{
public:
	 bool Start();
	 void Update();
	const CVector3& GetPlayerPosition()const
	{
		return m_position;
	}
private:
	CharacterController m_charaCon;
	bool m_first = false;
	CVector3 m_position = CVector3::Zero();
};

