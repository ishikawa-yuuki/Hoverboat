#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{

	m_sprite.Init(L"Assets/sprite/test.dds",280,86);
	m_bgm = new CSoundSource();
	m_bgm->Init(L"Assets/sound/Title.wav");
	m_bgm->SetVolume(0.8f);

	m_decided = new CSoundSource();
	m_decided->Init(L"Assets/sound/decided.wav");

	m_bgm->Play(true);
	
}


Title::~Title()
{
	
}
void Title::Update() 
{
	
	if (g_pad->IsTrigger(enButtonA)) {
		m_trigger = true;
		m_decided->Play(false);
		
		
		
	}
	if (m_trigger)
	{
		m_timer += GameTime().GetFrameDeltaTime();
		m_fontTimer += m_addPress * GameTime().GetFrameDeltaTime();
		
	}
	else 
	{
		m_fontTimer += m_add * GameTime().GetFrameDeltaTime();
	}

	if (m_timer >= 1.0f)
	{
		//ƒQ[ƒ€‚Ö
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
		delete(m_bgm);
		delete(m_decided);
	}
	m_color = sin(m_fontTimer) * m_sinWave + m_sinWave;
}
void Title::Render()
{
	/*CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, 1 },
		{ 0, 0, 0 },
		{ 0,1,0 }
	);
	mProj.MakeOrthoProjectionMatrix(1280, 720, 0.1, 100);*/
	m_sprite.Draw();
}
void Title::PostRender()
{
	
	wchar_t output[13];	
	swprintf(output, L"PRESS ANYKEY");
	m_font.Begin();
	
	m_font.Draw(output, m_pos, { m_color,m_color,m_color, m_color },0.0f,m_scale);
	m_font.End();
	
}