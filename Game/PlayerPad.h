#pragma once
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

	void PlayerPad::CheckGhost() {}
	bool PlayerPad::IsPressAccel()
	{
		return g_pad->IsPress(enButtonRB1);
	}
	bool PlayerPad::IsPressJump()
	{
		return g_pad->IsPress(enButtonA);
	}
	CQuaternion PlayerPad::GetRotation()
	{
		return m_rot;
	}
	CVector3 PlayerPad::GetDirection()
	{
		return m_moveDirection;
	}
	float PlayerPad::GetLstickXF()
	{
		return g_pad[0].GetLStickXF()* 1.4f;
	}
private:
	CVector3 m_moveDirection = g_camera3D.GetForward();//�ړ����̉�����
	CVector3 m_cameraForward = g_camera3D.GetForward();//�J�����̑O���������擾�B
	CQuaternion m_rot = CQuaternion::Identity();
	bool m_first = false;
};