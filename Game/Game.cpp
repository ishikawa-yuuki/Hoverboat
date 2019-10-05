#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Pass.h"
#include "BackGround.h"
Game::Game()
{
	m_player =  g_goMgr.NewGameObject<Player>();
	m_enemy = g_goMgr.NewGameObject<Enemy>();
	m_gc     =  g_goMgr.NewGameObject<GameCamera>();
	m_gc->GetInfoPlayer(m_player);
	//m_sprite.Init(L"Assets/sprite/title.dds", 200, 200);
	
	m_level.Init(L"Assets/level/Stage_defult.tkl", [&](LevelObjectData & objdata)
	{
		if (objdata.EqualObjectName(L"Stage_Defult")) {
			m_bg = g_goMgr.NewGameObject<BackGround>();
			return true;
		}
		else if (objdata.EqualObjectName(L"Pass")) {
			Pass* pass = g_goMgr.NewGameObject<Pass>();
			pass->SetPosition(objdata.position);
			m_passList.push_back(pass);
			return true;
		}

		return false;
	});
	m_enemy->GetPassObjectList(m_passList);
}


Game::~Game()
{
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_bg);
	g_goMgr.DeleteGameObject(m_gc);
}
void Game::Update()
{
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	//m_sprite.UpdateWorldMatrix(CVector3::Zero(),rot,CVector3::One());
}
void Game::Render()
{
	/*CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, 1 },
		{ 0, 0, 0 },
		{ 0,1,0 }
	);
	mProj.MakeOrthoProjectionMatrix(1280, 720, 0.1, 100);
	m_sprite.Draw(mView, mProj);*/
}
