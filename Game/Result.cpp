#include "stdafx.h"
#include "Result.h"
#include "GameData.h"
#include "Title.h"
Result::Result()
{
	m_gamedata = &GameData::GetInstance();
	m_sprite.Init(L"Assets/sprite/gure.dds", 800, 540);
	m_sprite.SetMulColor(CVector4{ 0.5f,0.5f,0.5f,1.0f });
	m_said = new CSoundSource;
	m_said->Init(L"Assets/sound/said.wav");
	m_said->Play(false);
}
Result::~Result()
{
}
void Result::Update()
{
	
	if (g_pad->IsTrigger(enButtonA)&&m_open)
	{	//ƒ^ƒCƒgƒ‹‚Ö
		g_goMgr->NewGameObject<Title>();
		delete(m_said);
		g_goMgr->DeleteGameObject(this);
	}

	if (!m_spriteX)
	{
		m_scaleY = sin(m_count) * 0.5f + 0.5f;
		if (m_count <= 1.0f)
		{
			m_count += 10 * GameTime().GetFrameDeltaTime();
		}
		else {
			m_count = 0.0f;
			m_spriteX = true;
		}
		
	}
	else if(!m_open)
	{
		m_scaleX = sin(m_count) * 0.5f + 0.5f;
		if (m_count <= 1.0f)
		{
			m_count += 15 * GameTime().GetFrameDeltaTime();
		}
		else {
			m_count = 1.0f;
			m_open = true;
		}
		
	}
	
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), { m_scaleX,m_scaleY,1.0f });
}
void Result::Render()
{
	m_sprite.Draw();
}
void Result::PostRender()
{
	if (m_open)
	{

		wchar_t output[7];
		wchar_t output2[3];
		wchar_t output3[12];
		wchar_t output4[15];
		
		swprintf_s(output, L"Result");
		m_font.Begin();
		m_font.Draw(output, { -630.0f,350.0f }, CVector4::White(), 0.0f, 2.5f);
		m_font.End();
		for (int i = 0; i < m_gamedata->GetListSize(); i++) {

			swprintf_s(output2, L"%d", m_rank + i);

			if (m_gamedata->GetNum(i) == 0)
			{
				swprintf_s(output3, L"Player: %d ", m_gamedata->GetNum(i));
			}
			else {
				swprintf_s(output3, L"    AI: %d ", m_gamedata->GetNum(i));
			}

			swprintf_s(output4, L"%d:%002d:%0.0f", m_gamedata->GetMinute(i), m_gamedata->GetSeond(i), m_gamedata->GetComma(i));
			
			m_font.Begin();
			m_font.Draw(output2, { -250.0f ,m_fontY + i * m_row }, CVector4::White(), 0.0f, 1.8f);
			m_font.Draw(output3, { -150.0f ,m_fontY + i * m_row }, CVector4::White(), 0.0f, 1.5f);
			m_font.Draw(output4, {  100.0f ,m_fontY + i * m_row }, CVector4::Yellow(), 0.0f, 1.5f);
			m_font.End();
		}
		
	}
}