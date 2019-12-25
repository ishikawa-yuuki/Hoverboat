/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */


#include "stdafx.h"
#include "physics/PhysicsStaticObject.h"
void PhysicsStaticObject::Release()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
void PhysicsStaticObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	RigidBodyInfo rbInfo;
	rbInfo.collider = m_collider.get();
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	g_physics.AddRigidBody(m_rigidBody);
}
void PhysicsStaticObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot)
{
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(skinModel, nullptr);
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ�����B
	g_physics.AddRigidBody(m_rigidBody);
}
