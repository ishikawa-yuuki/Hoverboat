#pragma once
#include "character/CharacterController.h"
class PlayerMove 
{
public:
	 bool Start();
	 void Update();
	 /// <summary>
	/// 回転処理
	/// </summary>
	 void Rotation();
	 /// <summary>
	 /// 移動処理
	 /// </summary>
	 void Move();
	 /*!
	  *@brief	PlayerのPositionを取得。
	  */
	const CVector3& GetPlayerPosition()const
	{
		return m_position;
	}
	/*!
	 *@brief	PlayerのCQuaternionを取得。
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

