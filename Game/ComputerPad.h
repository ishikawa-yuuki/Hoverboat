#pragma once
#include "GamePad.h"
class CoursePass;
class ComputerPad : public GamePad
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ComputerPad();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ComputerPad();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
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
	void Jump() {};

	/// <summary>
	/// �S�[�X�g(�����蔻��)
	/// </summary>
	void HitGhost();

	void HitCourcePass();
	void HitReStartPos() {};
	void isDead() {};
	void NotHitPass();

	/// <summary>
	/// L�X�e�B�b�N�擾
	/// </summary>
	float GetLstickXF()
	{
		return m_stickL;
	}

	/// <summary>
	/// �A�N�Z���{�^���擾
	/// </summary>
	bool  IsPressAccel()
	{
		return m_pressAccel;
	}

	/// <summary>
	/// �W�����v�{�^���擾
	/// </summary>
	bool  IsPressJump()
	{
		return m_pressJump;
	}

	/// <summary>
	/// �����擾
	/// </summary>
	CQuaternion GetRotation()
	{
		return m_rot;
	}

	/// <summary>
	/// �ړ������擾
	/// </summary>
	CVector3    GetDirection() { return m_cpDirection; }

	/// <summary>
	/// �|�W�V�����ݒ�
	/// </summary>
	void SetPosition(CVector3 const& pos) { m_position = pos; }

	/// <summary>
	/// �p�X���X�g�ɏ���ݒ�
	/// </summary>
	/// <param name="List">�R�[�X�p�X���X�g</param>
	/// <returns></returns>
	const std::vector<CoursePass*>& SetPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_courcePassList = List;
		return m_courcePassList;
	}
private:
	std::vector<CoursePass*> m_courcePassList;				//�R�[�X�ʉߔ���p
	std::vector<bool> m_hitPass;							//�p�X�q�b�g�ʒm
	bool m_pressAccel		   = true;						//�A�N�Z���{�^��
	bool m_pressJump		   = false;						//�W�����v�{�^��
	bool m_first			   = false;						//Update�ň�x�������s
	bool m_hit				   = false;						//�p�X�q�b�g�ʒm����
	float m_stickL			   = 0.0f;						//L�X�e�B�b�N
	int	  m_passNum		       = 0;							//�ʉߍς݃p�X�ԍ�
	CQuaternion m_rot		   = CQuaternion::Identity();	//����
	CVector3 m_position		   = CVector3::Zero();			//�|�W�V����
	CVector3 m_passDirection   = CVector3::Zero();			//Pass�̉�����
	CVector3 m_cpDirection     = CVector3::Zero();			//Computer�̉�����
	
};

