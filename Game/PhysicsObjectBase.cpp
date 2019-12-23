#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include "BoxCollider.h"
#include "physics/CapsuleCollider.h"
#include "physics/MeshCollider.h"
using namespace std;
void PhysicsObjectBase::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot);
}
void PhysicsObjectBase::CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height)
{
	Release();
	auto capusuleCollider = make_unique<CapsuleCollider>();
	capusuleCollider->Create(radius, height);
	m_collider = move(capusuleCollider);
	CreateCommon(pos, rot);
}

//void PhysicsObjectBase::CreateSphere(CVector3 pos, CQuaternion rot, float radius)
//{
//	Release();
//	auto sphereCollider = make_unique<CSphereCollider>();
//	sphereCollider->Create(radius);
//	m_collider = move(sphereCollider);
//	CreateCommon(pos, rot);
//}

void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, const SkinModel& skinModel)
{
	Release();
	auto meshCollider = make_unique<MeshCollider>();
	meshCollider->CreateFromSkinModel(skinModel, nullptr);
	m_collider = move(meshCollider);
	CreateCommon(pos, rot);
}