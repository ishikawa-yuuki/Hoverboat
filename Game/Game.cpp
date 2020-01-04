#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Pass.h"
#include "BackGround.h"
#include "RenderTarget.h"
#include "ShadowMap.h"
Game::Game()
{	
	
	
	m_level.Init(L"Assets/level/Stage_defult.tkl", [&](LevelObjectData & objdata)
	{
		if (objdata.EqualObjectName(L"Stage_Defult")) {
			m_bg = g_goMgr->NewGameObject<BackGround>();
			return true;
		}
		else if (objdata.EqualObjectName(L"Pass")) {
			Pass* pass = g_goMgr->NewGameObject<Pass>();
			pass->SetPosition(objdata.position);
			m_passList.push_back(pass);
			return true;
		}

		return false;
	});
	m_gc = g_goMgr->NewGameObject<GameCamera>();
	//0番目はユーザーが操作するプレイヤー
	m_player[0] = g_goMgr->NewGameObject<Player>();
	m_player[0]->SetPad(&m_playerPad);
	m_gc->GetInfoPlayer(m_player[0]);
	//1番目はコンピューターが操作するプレイヤー
	m_player[1] = g_goMgr->NewGameObject<Player>();
	//m_player[1]->SetPad(&m_playerPad);
	m_player[1]->SetPad(&m_comPad);

	//m_player[0]->GetPlayerMove()->GetInfoEnemy(m_enemy);
	//m_sprite.Init(L"Assets/sprite/title.dds", 200, 200);
	//m_enemy->GetPassObjectList(m_passList);
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
}


Game::~Game()
{
	for (Player* pl : m_player) {
		if (pl) {
			g_goMgr->DeleteGameObject(pl);
		}
	}
	g_goMgr->DeleteGameObject(m_bg);
	g_goMgr->DeleteGameObject(m_gc);
	for (auto& pass : m_passList) {
		g_goMgr->DeleteGameObject(pass);
	}
}
void Game::Update()
{
	/*CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);*/
	//m_sprite.UpdateWorldMatrix(CVector3::Zero(),rot,CVector3::One());
	//m_player->GetPlayerMove()->GetInfoEnemy(m_enemy);
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
