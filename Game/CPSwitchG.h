/*!
 *@brief	CP�̕����]���p
			�S�[�X�g�I�u�W�F�N�g�N���X
 */

#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"

class CPSwitchG : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CPSwitchG();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CPSwitchG();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
	void Start(); 

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(); 

	/// <summary>
	/// �`��
	/// </summary>
	void Render() {};


	void Release();
	//CP�̍��W��ݒ�
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//CP�̉�]��ݒ�
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//CP�̑傫����ݒ�
	void SetScale(const CVector3& scale) {
		m_scale = scale*1000;
	}

	/// <summary>
	/// �����蔻��擾
	/// </summary>
	/// <returns></returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}

	/// <summary>
	/// �p�X������
	/// </summary>
	/// <returns></returns>
	bool InitPass()
	{
		m_t = false;
		return m_t;
	}

	/// <summary>
	/// �p�X�ʉ�
	/// </summary>
	/// <returns></returns>
	bool OverPass()
	{
		m_t = true;
		return m_t;
	}

	/// <summary>
	///	�p�X���擾
	/// </summary>
	/// <returns></returns>
	bool GetPass()const
	{
		return m_t;
	}
private:
	bool m_t = false;								//�p�X�ʉߎ擾�p
	bool m_start = false;							//��x�������s����p
	PhysicsGhostObject m_ghost;						//�����蔻��
	CVector3 m_position = CVector3::Zero();			//�|�W�V����
	CQuaternion m_rot = CQuaternion::Identity();	//����
	CVector3 m_scale = CVector3::One();				//�傫��
};