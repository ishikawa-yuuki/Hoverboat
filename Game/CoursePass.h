#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"

class CoursePass : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CoursePass();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CoursePass();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
	void Start();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	void Render() {};
	void Release();
	/// <summary>
	/// Position�ݒ�
	/// </summary>
	/// <param name="pos">pos</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// Rotation�ݒ�
	/// </summary>
	/// <param name="rot">rot</param>
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}

	/// <summary>
	/// Scale�ݒ�
	/// </summary>
	/// <param name="scale">scale</param>
	void SetScale(const CVector3& scale) {
		m_scale = scale * 1000;
	}

	/// <summary>
	/// Position�擾
	/// </summary>
	/// <returns>CoursePass��Position</returns>
	CVector3 GetPosition()const
	{
		return m_position;
	}
	bool InitPass()
	{
		over = false;
		return over;
	}
	bool HitPass()
	{
		over = true;
		return over;
	}
	bool GetPass()const
	{
		return over;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	PhysicsGhostObject m_ghost;  //�S�[�X�g(�����蔻��)
	bool over = false;
	bool m_start = false;
};

