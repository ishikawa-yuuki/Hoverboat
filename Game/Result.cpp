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
	/*wchar_t output[9];
	wchar_t output2[15];
	swprintf_s(output, L"NUM: %d ",m_gamedata[0].GetNum(0));
	swprintf_s(output2, L"%d:%002d:%0.0f", m_gamedata->GetMinute(0), m_gamedata->GetSeond(0), m_gamedata->GetComma(0));
	m_font.DrawScreenPos(output, { 350.0f,150.0f }, CVector4::White(), { 1.8f,1.8f });
	m_font.DrawScreenPos(output2, { 750.0f,150.0f }, CVector4::Yellow(), { 1.8f, 1.8f });

	
	wchar_t output3[7];
	swprintf_s(output3, L"Result");
	m_font.DrawScreenPos(output3, { 0.0f,0.0f }, CVector4::White(), {2.5f,2.5f});*/

}