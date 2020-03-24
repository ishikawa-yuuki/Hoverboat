#pragma once
#include "GameObjectManager.h"
class Player;
class GameData;
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
	GameData* m_gamedata = nullptr;
	CVector3 m_target = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_rePosition = CVector3::Zero();
	CVector3 m_reTarget = CVector3::Zero();
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	CVector3 m_toCameraPos = { 0.0f, 0.0f, 350.0f };
	CVector3 m_retoCameraPos = { 0.0f, 0.0f, 350.0f };
	//push,pup�̓O���t�B�b�N�ɑ�p���
	//�t�H��t���̂܂܂��ҁ[
	
};

