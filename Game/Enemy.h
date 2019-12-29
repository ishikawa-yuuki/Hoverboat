#pragma once
#include "GameObjectManager.h"
//#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
class Pass;
class GamePad;
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
	GamePad* m_gamePad = nullptr;
	/*CharacterController m_charaCon;*/
	PhysicsGhostObject m_ghost;
	std::vector<Pass*> m_passList;
	CVector3 m_accel = CVector3::Zero();	//加速度。
	CVector3 m_PassDirection = CVector3::Zero();//Passの奥方向
	CVector3 m_ComDirection = CVector3::Zero();//Computerの奥方向
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_diff = CVector3::Zero();
	float	 m_movePower = 0.00001f;// 移動速度
	int		 i = 0;

};

