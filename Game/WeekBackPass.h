#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
class WeekBackPass :public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WeekBackPass();

	/// <summary>
	///�@�f�X�g���N�^
	/// </summary>
	~WeekBackPass();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
	void Start();

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();

	void Render() {};
	/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
	void Release();

	//CP�̍��W��ݒ�
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}

	//CP�̑傫����ݒ�
	void SetScale(const CVector3& scale) {
		m_scale = scale*1000;
	}

	/// <summary>
	/// �S�[�X�g(�����蔻��)�擾�B
	/// </summary>
	/// <returns>�S�[�X�g</returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}

	void InitPass()
	{
		m_over = false;
	}

	void  HitPass()
	{
		m_over = true;
	}

	/// <summary>
	/// �p�X�ʉߔ���
	/// </summary>
	bool GetPass()const
	{
		return m_over;
	}
private:
	bool m_over	 = false;
	bool m_start = false;
	PhysicsGhostObject m_ghost;
	CVector3 m_position	= CVector3::Zero();
	CQuaternion m_rot	= CQuaternion::Identity();
	CVector3 m_scale	= CVector3::One();
};

