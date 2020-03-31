#include "stdafx.h"
#include "Result.h"
#include "GameData.h"
#include "Title.h"
Result::Result()
{
	m_gamedata = &GameData::GetInstance();
	m_said = new CSoundSource;
	m_said->Init(L"Assets/sound/said.wav");
	m_said->Play(false);
}
Result::~Result()
{
}
void Result::Update()
{
	
	if (g_pad->IsTrigger(enButtonA))
	{	//ƒ^ƒCƒgƒ‹‚Ö
		g_goMgr->NewGameObject<Title>();
		g_goMgr->DeleteGameObject(this);
	}

}
void Result::Render()
{

}
void Result::PostRender()
{
	wchar_t output[12];
	wchar_t output2[15];
	wchar_t output3[7];
	for (int i = 0; i < m_gamedata->GetListSize(); i++) {
		if (m_gamedata->GetNum(i) == 0)
		{
			swprintf_s(output, L"Player: %d ", m_gamedata->GetNum(i));
		}
		else {
			swprintf_s(output, L"    AI: %d ", m_gamedata->GetNum(i));
		}

		swprintf_s(output2, L"%d:%002d:%0.0f", m_gamedata->GetMinute(i), m_gamedata->GetSeond(i), m_gamedata->GetComma(i));
		swprintf_s(output3, L"Result");
		m_font.Begin();
		m_font.Draw(output, { -200.0f,m_fontY + i * m_row }, CVector4::White(), 0.0f, 1.8f);
		m_font.Draw(output2, { 50.0f,m_fontY + i * m_row }, CVector4::Yellow(), 0.0f, 1.8f);
		m_font.Draw(output3, { -630.0f,350.0f }, CVector4::White(), 0.0f, 2.5f);
		m_font.End();
	}
}