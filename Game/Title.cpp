#include "stdafx.h"
#include "Title.h"
#include "Character_Select.h"

Title::Title()
{
	//初期化
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
	
	

	//フォント点滅
	if (m_trigger)
	{
		m_timer += GameTime().GetFrameDeltaTime();
		m_fontTimer += m_addPress * GameTime().GetFrameDeltaTime();
		
	}
	else //通常表示
	{
		
		if (g_pad->IsPressAnyKey()&&m_timer > m_ragu) {
			m_trigger = true;
			m_decided->Play(false);
			m_timer = 0.0f;
			return;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		m_fontTimer += m_add * GameTime().GetFrameDeltaTime();
	}
	m_color = sin(m_fontTimer) * m_sinWave + m_sinWave;

	if (m_trigger && m_timer >= 1.0f)
	{
		//キャラ選択へ
		g_goMgr->NewGameObject<Character_Select>();
		delete(m_bgm);
		delete(m_decided);
		g_goMgr->DeleteGameObject(this);
		
	}
	
}
void Title::Render()
{
	//スプライト表示
	m_sprite.Draw();
}
void Title::PostRender()
{
	//フォント表示
	wchar_t output[13];	
	swprintf(output, L"PRESS ANYKEY");
	m_font.Begin();
	
	m_font.Draw(output, m_pos, { m_color,m_color,m_color, m_color },0.0f,m_scale);
	m_font.End();
	
}