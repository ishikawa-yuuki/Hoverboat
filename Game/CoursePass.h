#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"

class CoursePass : public IGameObject
{
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	PhysicsGhostObject m_ghost;
	bool over = false;
	bool m_start = false;
public:
	CoursePass();
	~CoursePass();
	void Start() {
		m_ghost.CreateBox(
			m_position,
			m_rot,
			m_scale
		);
		m_start = true;
	}
	void Update()
	{
		if (!m_start) {
			Start();
		}
	};
	void Render() {};
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale * 1000;
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
	bool HitPass()
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

