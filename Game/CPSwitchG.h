/*!
 *@brief	CPの方向転換用
			ゴーストオブジェクトクラス
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
	//CPの座標を設定
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//CPの回転を設定
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//CPの大きさを設定
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