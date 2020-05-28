#pragma once
#include "GameObjectManager.h"
#include "level/Level.h"
#include "Sprite.h"
class Player;
class GameData;
class Character_Select : public  IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Character_Select();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Character_Select();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	enum Chara {
		//最小値
		enState_First,
		Metal,
		Brick,
		Wood,
		//最大値
		enState_Last
	};
private:
	Chara m_selctChara = Metal;							//キャラ番号
	Level m_level;										//レベル
	Sprite m_frame;										//フレーム
	Sprite m_metal;										//UI
	Sprite m_brick;										
	Sprite m_wood;										
	SkinModel m_model;									//背景。
	SkinModel m_modeldai;								//台
	GameData* m_gamedata = nullptr;						//ゲームデータ
	Player* m_player	 = nullptr;						//プレイヤー
	CVector3 m_metalPos = { -400.0f,200.0f,0.0f };		//UIポジション
	CVector3 m_brickPos = { -400.0f,100.0f,0.0f };		
	CVector3 m_woodPos  = { -400.0f,  0.0f,0.0f };		
	CVector3 m_framePos = m_metalPos;					//フレームのポジション
	CVector3 m_position = CVector3::Zero();				//背景ポジション
	CVector3 m_posDai	= CVector3::Zero();				//台のポジション
	CVector3 m_scale	= CVector3::One();				//背景大きさ
	CVector3 m_scaledai = CVector3::One();				//台大きさ
	CQuaternion m_rot	= CQuaternion::Identity();		//背景向き
	float m_time		= 0.0f;							//フレームの移動の制限
};

