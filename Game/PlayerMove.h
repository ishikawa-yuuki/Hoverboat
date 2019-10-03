#pragma once
#include "character/CharacterController.h"
class PlayerMove 
{
public:
	 bool Start();
	 void Update();
	 /// <summary>
	/// ‰ñ“]ˆ—
	/// </summary>
	 void Rotation();
	 /// <summary>
	 /// ˆÚ“®ˆ—
	 /// </summary>
	 void Move();
	 /*!
	  *@brief	Player‚ÌPosition‚ğæ“¾B
	  */
	const CVector3& GetPlayerPosition()const
	{
		return m_position;
	}
	/*!
	 *@brief	Player‚ÌCQuaternion‚ğæ“¾B
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
private:
	CharacterController m_charaCon;
	bool m_first = false;
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_position  = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

