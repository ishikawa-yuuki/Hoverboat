#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "Sprite.h"
#include "CFont.h"
class Title:public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Title();
	/// <summary>
	///　デストラクタ
	/// </summary>
	~Title();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender() override;
private:
	Sprite m_sprite;									//スプライト
	CFont m_font;										//フォント
	CSoundSource* m_bgm		= nullptr;					//BGM。
	CSoundSource* m_decided = nullptr;					//決定音
	const int m_add			= 3;						//サインカーブ(緩やか)
	const int m_addPress	= 20;						//サインカーブ(早く)	
	const float m_sinWave	= 0.5;						//サインの波の指定
	float  m_color			= 1.0f;						//カラー
	float m_timer			= 0.0f;						//タイム
	float m_fontTimer		= 0.0f;						//フォントタイム
	float m_scale			= 2.0f;						//大きさ
	bool m_trigger			= false;					//フォント表示切替
	CVector2 m_pos			= { -100.0f,-300.0f };		//フォントpos

};

