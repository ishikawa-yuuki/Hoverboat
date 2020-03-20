#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	
	////カメラを設定。
	//g_camera3D.SetPosition({ 0.0f, 1000.0f, 2200.0f });
	//g_camera3D.SetTarget({ 0.0f, 200.0f, 0.0f });
	//g_camera3D.Update();
	m_sprite.Init(L"Assets/sprite/title.dds", 1280, 720);
	m_bgm = new CSoundSource();
	m_bgm->Init(L"Assets/sound/Title.wav");
	m_bgm->SetVolume(0.8f);
	m_bgm->Play(true);
}


Title::~Title()
{
	
}
void Title::Update() 
{
	//m_sprite.Update(CVector3::Zero(),CQuaternion::Identity(),CVector3::One());
	
	if (g_pad->IsTrigger(enButtonA)) {
		m_trigger = true;
		
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
		//ゲームへ
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
		delete(m_bgm);
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

}
void Title::PostRender()
{
	m_sprite.Draw();
	wchar_t output[13];
	swprintf(output, L"PRESS ANYKEY");
	m_font.DrawScreenPos(output, m_pos, { m_color,m_color,m_color, m_color }, m_scale);
	
}