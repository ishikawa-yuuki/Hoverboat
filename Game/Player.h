#pragma once
#include "GameObjectManager.h"
class GamePad;
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
	void SetPad(GamePad* gamePad)
	{
		m_gamePad = gamePad;
	}
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	GamePad* m_gamePad = nullptr;
	enum HumanAnimationClip {
		enAnimationClip_test,
		enAnimationClip_num
	};
	AnimationClip m_animClip[enAnimationClip_num];
	Animation m_animation;
};

