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
	int GetMinute()
	{
		return m_minute;
	}
	int GetSeond()
	{
		return m_second;
	}
	float GetComma()
	{
		return m_comma;
	}

private:
	CSoundSource* m_countSound = nullptr; //カウントダウンの音
	CFont m_font;
	bool m_raceStart = false;
	float m_count	 = 3.0f;
	float m_timer	 = 0.0f;
	float m_comma	 = 0.0f; 
	int m_second	 = 0;
	int m_minute	 = 0;
	int m_integer	 = 0;
	
};

