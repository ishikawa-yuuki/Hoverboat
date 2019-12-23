#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "physics/CapsuleCollider.h"
#include "BoxCollider.h"
using namespace std;
void PhysicsGhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		g_physics.RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}
void PhysicsGhostObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	m_ghostObject.setCollisionFlags(4);
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);

	//ï®óùÉGÉìÉWÉìÇ…ìoò^ÅB
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}
