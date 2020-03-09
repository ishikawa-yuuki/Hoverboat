#include "stdafx.h"
#include "RaceTimer.h"



RaceTimer::RaceTimer()
{
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
	//���[�X���v���p
	wchar_t output[256];
	wchar_t output2[256];
	swprintf_s(output, L"Time ");
	swprintf_s(output2, L"%d:%002d:%0.0f", m_minute, m_second, m_comma);
	m_font.DrawScreenPos(output, { 550.0f,20.0f }, CVector4::White(), { 1.5f,1.5f });
	m_font.DrawScreenPos(output2, { 600.0f,15.0f }, CVector4::Yellow(), { 1.8f, 1.8f });

	//�X�^�[�g�J�E���g
	if (!GetRaceStart()) {
		wchar_t output3[256];
		swprintf_s(output3, L"%d:%002.f", 0, m_count);
		m_font.DrawScreenPos(output3, { 600.0f,200.0f }, CVector4::White(), { 2.5f, 2.5f });
	}
}