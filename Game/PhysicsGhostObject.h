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
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでゴーストオブジェクトを削除したい場合に呼び出してください。
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
		* @brief	メッシュの静的オブジェクトを作成。
		*@param[in]	skinModel	スキンモデル。
		*@param[in]	pos			座標。
		*@param[in]	rot			回転。
		*/
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot);
	void CreateCapsule(float radius, float height, const CVector3& position);
private:
	bool				m_isRegistPhysicsWorld = false; //!<物理ワールドに登録しているかどうかのフラグ。
	btGhostObject		m_ghostObject;//!<ゴースト
	CapsuleCollider m_collider;
};

