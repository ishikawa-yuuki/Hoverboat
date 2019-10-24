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
	float m_movePower = 1000.0f;// 移動速度
	float m_moveForceMultiplier = 2.0f; // 移動速度の入力に対する追従度
	float m_movePress = 0.0f;
	bool m_first = false;
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_moveVector = CVector3::Zero();
	CVector3 m_position  = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

