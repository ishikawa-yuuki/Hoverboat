#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
#include "Sprite.h"
class GameData;
class Result : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Result();

	/// <summary>
	///　デストラクタ
	/// </summary>
	~Result();

	/// <summary>
	/// 更新。
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	void PostRender()override;

private:
	CSoundSource* m_said = nullptr;		//表示音。
	GameData* m_gamedata = nullptr;		//ゲームデータ				
	CFont m_font;						//リザルトフォント
	Sprite m_sprite;					//スプライト
	bool m_open		= false;			//リザルト表示時
	bool m_spriteX  = false;			//スプライト表示の際の表現用
	const float m_fontY = 150.0f;		//フォントpos
	float m_row			= -70.0f;		//フォントpos
	float m_count		= 0.0f;			//サインカーブ
	float m_scaleX		= 0.01f;		//Xのスケール
	float m_scaleY		= 0.01f;		//Yのスケール
	int m_rank			= 1;			//ランク
};

