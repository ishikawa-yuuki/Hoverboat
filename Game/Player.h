#pragma once
#include "GameObjectManager.h"
#include "PlayerMove.h"
class GamePad;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();
	/*!
	 *@brief	Player��Position���擾�B
	 */
	const CVector3& GetPosition()const
	{
		return m_position;
	}
	/*!
	 *@brief	Player��CQuaternion���擾�B
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
	PlayerMove* GetPlayerMove()
	{
		return &playerMove;
	}
	void SetPad(GamePad* gamePad)
	{
		m_gamePad = gamePad;
		playerMove.SetPad(gamePad);
	}
private:
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	PlayerMove playerMove;
	GamePad* m_gamePad = nullptr;
};

