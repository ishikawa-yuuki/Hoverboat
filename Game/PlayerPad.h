#pragma once
#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
#include "GamePad.h"
class PlayerPad : public GamePad
{
public:
	PlayerPad();
	~PlayerPad();
	bool Start();
	/// <summary>
   /// ��]����
   /// </summary>
	void Rotation();
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �W�����v����
	/// </summary>
	void Jump();
	/// <summary>
	/// ���񔻒菈��
	/// </summary>
	void Check();
	float PlayerPad::GetLstickXF()
	{
		return g_pad[0].GetLStickXF();
	}
	bool PlayerPad::IsPressAccel()
	{
		return g_pad->IsPress(enButtonRB1);
	}
	bool PlayerPad::IsPressJump()
	{
		return g_pad->IsPress(enButtonA);
	}
	CVector3 PlayerPad::GetPosition()
	{
		return m_position;
	}
	CQuaternion PlayerPad::GetRotation()
	{
		return m_rot;
	}
	void  UpdatePad();
private:
	CharacterController m_charaCon;
	float m_movePower = 100.0f;// �ړ����x
	float m_moveForceMultiplier = 2.0f; // �ړ����x�̓��͂ɑ΂���Ǐ]�x
	float m_friction = 0.98f;   //���C�x
	bool m_first = false;
	bool m_over = true;
	CVector3 m_accel = CVector3::Zero();	//�����x�B
	CVector3 m_jump = CVector3::Zero();     //�W�����v�̉����x
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_position = { 10.0f,20.0f,0.0f };
	CVector3 m_moveDirection = g_camera3D.GetForward();//�ړ����̉�����
	CVector3 m_cameraForward = g_camera3D.GetForward();//�J�����̑O���������擾�B
	CQuaternion m_rot = CQuaternion::Identity();
};