
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
	//CPÇÃç¿ïWÇê›íË
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//CPÇÃëÂÇ´Ç≥Çê›íË
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
	void InitPass()
	{
		m_over = false;
	}
	void  HitPass()
	{
		m_over = true;
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

