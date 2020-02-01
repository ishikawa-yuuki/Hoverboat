#pragma once
#include "GameObjectManager.h"
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void Render() {};
	Player* GetInfoPlayer(Player* pl)
	{
		m_player = pl;
		return m_player;
	}
private:
	Player* m_player =nullptr;
	CVector3 m_target = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
	//注視点から視点までのベクトルを設定。
	CVector3 m_toCameraPos = { 0.0f, 110.0f, 380.0f };
};

