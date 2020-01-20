#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	//ƒJƒƒ‰‚ðÝ’èB
	/*g_camera3D.SetPosition({ 0.0f, 1000.0f, 2200.0f });
	g_camera3D.SetTarget({ 0.0f, 200.0f, 0.0f });
	g_camera3D.Update();*/
	m_sprite.Init(L"Assets/sprite/title.dds", 1280, 720);
}


Title::~Title()
{
}
void Title::Update() 
{
	//m_sprite.Update(CVector3::Zero(),CQuaternion::Identity(),CVector3::One());
	if (g_pad->IsPressAnyKey()) 
	{
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
	}
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
	m_sprite.Draw(/*mView, mProj*/);
}
