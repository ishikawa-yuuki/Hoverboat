#pragma once
#include "Physics/CapsuleCollider.h"
class PhysicsGhostObject
{
public:
	~PhysicsGhostObject()
	{
		Release();
	};
	/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
	void Release();
	
	void SetPosition(const CVector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	void SetRotation(const CQuaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		rot.CopyTo(btRot);
		btTrans.setRotation(btRot);
	}
	/*!
		* @brief	���b�V���̐ÓI�I�u�W�F�N�g���쐬�B
		*@param[in]	skinModel	�X�L�����f���B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*/
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot);
	void CreateCapsule(float radius, float height, const CVector3& position);
private:
	bool				m_isRegistPhysicsWorld = false; //!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject		m_ghostObject;//!<�S�[�X�g
	CapsuleCollider m_collider;
};

