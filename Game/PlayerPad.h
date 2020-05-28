#pragma once
#include "GamePad.h"
class PlayerPad : public GamePad
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerPad();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerPad();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
	void Start();

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
	void Jump() {};
	void HitCourcePass() {};
	void HitReStartPos();
	void isDead();
	void PlayerPad::NotHitPass() {}
	void PlayerPad::HitGhost() {}
	/// <summary>
	/// �p�b�h����RB�{�^���̓��͎擾�B
	/// </summary>
	/// <returns></returns>
	bool PlayerPad::IsPressAccel()
	{
		return g_pad->IsPress(enButtonRB1);
	}
	/// <summary>
	/// �p�b�h����A�{�^���̓��͎擾�B
	/// </summary>
	/// <returns></returns>
	bool PlayerPad::IsPressJump()
	{
		return g_pad->IsPress(enButtonA);
	}
	/// <summary>
	/// �L�����̌����擾
	/// </summary>
	/// <returns></returns>
	CQuaternion PlayerPad::GetRotation()
	{
		return m_rot;
	}
	//�ړ������擾	
	CVector3 PlayerPad::GetDirection()
	{
		return m_moveDirection;
	}
	/// <summary>
	/// L�X�e�B�b�N�擾
	/// </summary>
	float PlayerPad::GetLstickXF()
	{
		return g_pad[0].GetLStickXF()* 1.4f;
	}
private:
	CVector3 m_moveDirection = g_camera3D.GetForward(); //�ړ����̉�����
	CVector3 m_cameraForward = g_camera3D.GetForward(); //�J�����̑O���������擾�B
	CQuaternion m_rot = CQuaternion::Identity();		//�L�����̌���
	CQuaternion m_reStartRot = CQuaternion::Identity(); //���X�^�[�g���̌���
	bool m_first = false;//��x�������s����p
};