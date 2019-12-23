/*!
 * @brief	静的オブジェクト。
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include "PhysicsObjectBase.h"

/*!
* @brief	静的物理オブジェクト
*/
class PhysicsStaticObject : public PhysicsObjectBase{
public:
	~PhysicsStaticObject()
	{
		Release();
	}
	/*!
	* @brief	解放。
	*/
	void Release() override final;
	/*!
	* @brief	座標と回転を設定。
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		m_rigidBody.SetPositionAndRotation(pos, rot);
	}
	RigidBody& GetRigidBody()
	{
		return m_rigidBody;
	}
	/*!
	* @brief	メッシュの静的オブジェクトを作成。
	*@param[in]	skinModel	スキンモデル。
	*@param[in]	pos			座標。
	*@param[in]	rot			回転。
	*/
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot);
	//↑逃げ
private:

	/*!
	* @brief	静的物理オブジェクト作成処理の共通処理。
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot) override final;
private:
	RigidBody m_rigidBody;				//!<剛体。
	MeshCollider m_meshCollider;
};
