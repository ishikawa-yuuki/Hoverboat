#pragma once
#include "GameObjectManager.h"
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
private:
	CFont m_font;
	float m_timer = 0.0f;
	float m_comma = 0.0f; 
	float m_count = 3.0f;
	int m_second = 0;
	int m_minute = 0;
	int m_integer = 0;
	bool m_raceStart = false;
};

