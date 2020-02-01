#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"

class CoursePass : public IGameObject
{
private:
	CVector3 m_position = CVector3::Zero();
	PhysicsGhostObject m_ghost;
	bool over = false;
public:
	CoursePass();
	~CoursePass();
	void Update() {};
	void Render() {};
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()const
	{
		return m_position;
	}
	bool InitPass()
	{
		over = false;
		return over;
	}
	bool OverPass()
	{
		over = true;
		return over;
	}
	bool GetPass()const
	{
		return over;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
};

