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
	CPSwitchG();
	~CPSwitchG();
	void Start() {
		m_ghost.CreateBox(
			m_position,
			m_rot,
			m_scale
		);
		m_start = true;
	}
	void Update() 
	{
		if (!m_start) {
			Start();
		}
	};
	void Render() {};
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
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
	bool InitPass()
	{
		m_t = false;
		return m_t;
	}
	bool OverPass()
	{
		m_t = true;
		return m_t;
	}
	bool GetPass()const
	{
		return m_t;
	}
private:
	bool m_t = false;
	bool m_start = false;
	PhysicsGhostObject m_ghost;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
};