#pragma once
#include "GameObjectManager.h"
#include "PlayerMove.h"

class PlayerMove;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();
private:
	SkinModel m_model;									//スキンモデル。
	//PlayerMove* m_pmove = nullptr;
//	PlayerMove* p = new PlayerMove();
	CVector3 m_position = CVector3::Zero();
	PlayerMove playerMove;
	
};

