
#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
class WeekBackPass :public IGameObject
{
public:
	WeekBackPass();
	~WeekBackPass();
	void Update()
	{
		m_ghost.SetPosition(m_position);
	};
	void Render() {};
	//CP‚ÌÀ•W‚ğİ’è
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//CP‚Ì‰ñ“]‚ğİ’è
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//CP‚Ì‘å‚«‚³‚ğİ’è
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
	bool InitPass()
	{
		m_over = false;
		return m_over;
	}
	bool OverPass()
	{
		m_over = true;
		return m_over;
	}
	bool GetPass()const
	{
		return m_over;
	}
private:
	bool m_over = false;
	PhysicsGhostObject m_ghost;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = { 1300.0f,100.0f,2200.0f };
};

