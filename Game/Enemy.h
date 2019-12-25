#pragma once
#include "GameObjectManager.h"
//#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
class Pass;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Update();
	void Render();
	const std::vector<Pass*>& GetPassObjectList(const std::vector<Pass*>& List)
	{
		m_passList = List;
		return m_passList;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
private:
	SkinModel m_model;
	/*CharacterController m_charaCon;*/
	PhysicsGhostObject m_ghost;
	std::vector<Pass*> m_passList;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_diff = CVector3::Zero();
	int i = 0;
};

