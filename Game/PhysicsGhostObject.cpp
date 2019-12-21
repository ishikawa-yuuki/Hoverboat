#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "physics/CapsuleCollider.h"

void PhysicsGhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		g_physics.RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}
void PhysicsGhostObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot)
{
	////���b�V���R���C�_�[���쐬�B
	//m_meshCollider.CreateFromSkinModel(skinModel, nullptr);
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//�����G���W���ɓo�^�B
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
void PhysicsGhostObject::CreateCapsule(float radius, float height, const CVector3& position)
{
	
	//�R���W�����쐬�B
	m_collider.Create(radius, height);
	btTransform btTrans;
	btTrans.setOrigin({ position.x, position.y, position.z });
	m_ghostObject.setWorldTransform(btTrans);

	//�����G���W���ɓo�^�B
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;

}
