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
	/*!
	 *@brief	PlayerのPositionを取得。
	 */
	const CVector3& GetPosition()const
	{
		return m_position;
	}
	/*!
	 *@brief	PlayerのCQuaternionを取得。
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
	PlayerMove* GetPlayerMove()
	{
		return &playerMove;
	}
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	PlayerMove playerMove;
};

