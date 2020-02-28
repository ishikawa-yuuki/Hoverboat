
#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
class WeekBackPass :public IGameObject
{
public:
	WeekBackPass();
	~WeekBackPass();
	void Start();
	void Update();
	void Render() {};
	void Release();
	//CPÇÃç¿ïWÇê›íË
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//CPÇÃëÂÇ´Ç≥Çê›íË
	void SetScale(const CVector3& scale) {
		m_scale = scale*1000;
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
	bool m_start = false;
	PhysicsGhostObject m_ghost;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
};

