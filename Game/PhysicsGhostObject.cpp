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
	////メッシュコライダーを作成。
	//m_meshCollider.CreateFromSkinModel(skinModel, nullptr);
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//物理エンジンに登録。
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
void PhysicsGhostObject::CreateCapsule(float radius, float height, const CVector3& position)
{
	
	//コリジョン作成。
	m_collider.Create(radius, height);
	btTransform btTrans;
	btTrans.setOrigin({ position.x, position.y, position.z });
	m_ghostObject.setWorldTransform(btTrans);

	//物理エンジンに登録。
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;

}
