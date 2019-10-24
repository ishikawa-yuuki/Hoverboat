#pragma once
#include "character/CharacterController.h"
class PlayerMove 
{
public:
	 bool Start();
	 void Update();
	 /// <summary>
	/// ��]����
	/// </summary>
	 void Rotation();
	 /// <summary>
	 /// �ړ�����
	 /// </summary>
	 void Move();
	 /*!
	  *@brief	Player��Position���擾�B
	  */
	const CVector3& GetPlayerPosition()const
	{
		return m_position;
	}
	/*!
	 *@brief	Player��CQuaternion���擾�B
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
private:
	CharacterController m_charaCon;
	float m_movePower = 1000.0f;// �ړ����x
	float m_moveForceMultiplier = 2.0f; // �ړ����x�̓��͂ɑ΂���Ǐ]�x
	float m_movePress = 0.0f;
	bool m_first = false;
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_moveVector = CVector3::Zero();
	CVector3 m_position  = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
};

