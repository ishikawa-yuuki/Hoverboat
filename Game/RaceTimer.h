#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
class RaceTimer:public IGameObject
{
public:
	RaceTimer();
	~RaceTimer();
	void Update();
	void Render();
	void RaceStart();
	void PostRender() override;
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
	CSoundSource* m_countSound = nullptr;
	CFont m_font;
	float m_count	= 3.0f;
	float m_timer	= 0.0f;
	float m_comma	= 0.0f; 
	int m_second	= 0;
	int m_minute	= 0;
	int m_integer	= 0;
	bool m_raceStart = false;
};

