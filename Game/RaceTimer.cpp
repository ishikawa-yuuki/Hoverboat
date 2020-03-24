#include "stdafx.h"
#include "RaceTimer.h"



RaceTimer::RaceTimer()
{
	m_countSound = new CSoundSource;
	m_countSound->Init(L"Assets/sound/count.wav");
}

RaceTimer::~RaceTimer()
{
}
void RaceTimer::RaceStart()
{

}
void RaceTimer::Update()
{
	if (GetRaceStart()) {
		m_timer += GameTime().GetFrameDeltaTime();
		m_second = m_timer;
		m_comma = m_timer - m_second;
		m_comma *= 10.0f;
		if (m_comma >= 9.5f)
		{
			m_comma = 0.0f;
		}
		if (m_timer >= 60.0f) {
			m_minute++;
			m_timer = m_timer - 60.0f;
		}
	}
	else {
		m_countSound->Play(false);
		m_count -= GameTime().GetFrameDeltaTime();
		if (m_count <= 0)
		{
			SetRaceStart();
		}
	}
}

void RaceTimer::Render()
{
}

void RaceTimer::PostRender()
{
	//レース中計測用
	wchar_t output[256];
	wchar_t output2[256];
	swprintf_s(output, L"Time ");
	swprintf_s(output2, L"%d:%002d:%0.0f", m_minute, m_second, m_comma);
	m_font.Begin();
	m_font.Draw(output, { -100.0f,350.0f }, CVector4::White(),  0.0f,1.5f );
	m_font.Draw(output2, { -50.0f,350.0f }, CVector4::Yellow(), 0.0f, 1.8f );

	//スタートカウント
	if (!GetRaceStart()) {
		wchar_t output3[256];
		swprintf_s(output3, L"%d:%002.f", 0, m_count);
		m_font.Draw(output3, { -50.0f,50.0f }, CVector4::White(),  0.0f, 2.5f );
	}
	m_font.End();
}
