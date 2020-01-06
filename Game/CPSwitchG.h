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
	void Update() {};
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
		m_scale = scale;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
private:
	PhysicsGhostObject m_ghost;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
};