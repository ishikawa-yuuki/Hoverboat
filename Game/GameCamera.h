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
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	CVector3 m_toCameraPos = { 0.0f, 40.0f, 250.0f };
};

