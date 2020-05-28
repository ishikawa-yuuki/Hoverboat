#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
class RaceTimer:public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RaceTimer();

	/// <summary>
    ///　デストラクタ
    /// </summary>
	~RaceTimer();

	/// <summary>
	/// 更新。
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render() {};

	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender() override;

	/// <summary>
	/// スタートしたか知る関数
	/// </summary>
	/// <returns></returns>
	bool GetRaceStart()
	{
		return m_raceStart;
	}
	void SetRaceStart()
	{
		m_raceStart = true;
	}
	//分取得
	int GetMinute()
	{
		return m_minute;
	}
	//秒取得
	int GetSeond()
	{
		return m_second;
	}
	//コンマ取得
	float GetComma()
	{
		return m_comma;
	}

private:
	CSoundSource* m_countSound = nullptr;   //カウントダウンの音
	CFont m_font;							//フォント
	bool m_raceStart = false;				//レーススタートの判断用
	float m_count	 = 3.0f;				//カウント時間(秒)
	float m_timer	 = 0.0f;				//タイム
	float m_comma	 = 0.0f;				//コンマ
	int m_second	 = 0;					//秒
	int m_minute	 = 0;					//分
	
};

