#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "StartRacePos.h"
#include "CPSwitchG.h"
#include "CoursePass.h"
#include "WeekBackPass.h"
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
		else if (objdata.EqualObjectName(L"coursePass")) {
			CoursePass* coursePass = g_goMgr->NewGameObject<CoursePass>();
			coursePass->SetPosition(objdata.position);
			coursePass->SetRotation(objdata.rotation);
			coursePass->SetScale(objdata.scale);
			m_coursePassList.push_back(coursePass);
			return true;
		}
		else if (objdata.EqualObjectName(L"WeekBackPass")) {
			WeekBackPass* weekbackPass = g_goMgr->NewGameObject<WeekBackPass>();
			weekbackPass->SetPosition(objdata.position);
			weekbackPass->SetScale(objdata.scale);
			m_weekbackPassList.push_back(weekbackPass);
			return true;
		}
		else if (objdata.EqualObjectName(L"Ghost")) {
			CPSwitchG* cpGhost = g_goMgr->NewGameObject<CPSwitchG>();
			cpGhost->SetPosition(objdata.position);
			cpGhost->SetRotation(objdata.rotation);
			cpGhost->SetScale(objdata.scale);
			m_CPGhostList.push_back(cpGhost);
			return true;
		}
		else if (objdata.EqualObjectName(L"StartRacePos")) {
			StartRacePos* startRacePos= g_goMgr->NewGameObject<StartRacePos>();
			startRacePos->SetPosition(objdata.position);
			m_startRacePosList.push_back(startRacePos);
			return true;
		}
		return false;
	});
	m_gc = g_goMgr->NewGameObject<GameCamera>();
	//0番目はユーザーが操作するプレイヤー
	for (int i = 0; i < 4; i++) {
		m_player[i] = g_goMgr->NewGameObject<Player>();
		m_player[i]->SetPosition(m_startRacePosList[i]->GetPosition());
		m_player[i]->SetPassObjectList(m_coursePassList);
		m_player[i]->SetGhostObjectList(m_CPGhostList);
		m_player[i]->SetWeekPassObjectList(m_weekbackPassList);
	}
	m_player[0]->SetPad(&m_playerPad);
	m_gc->GetInfoPlayer(m_player[0]);
	m_player[0]->SetChara(0);
	//1,2,3番目はコンピューターが操作するプレイヤー
	m_player[1]->SetPad(&m_comPad[0]);
	m_player[1]->SetChara(0);

	m_player[2]->SetPad(&m_comPad[1]);
	m_player[2]->SetChara(1);

	m_player[3]->SetPad(&m_comPad[2]);
	m_player[3]->SetChara(0);
	for (int i = 0; i < 3; i++) {
		m_comPad[i].SetPassObjectList(m_coursePassList);
	}
	
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
	for (auto& coursePass : m_coursePassList) {
		g_goMgr->DeleteGameObject(coursePass);
	}
	for (auto& weekbackPass : m_weekbackPassList) {
		g_goMgr->DeleteGameObject(weekbackPass);
	}
	for (auto& cpGhost : m_CPGhostList) {
		g_goMgr->DeleteGameObject(cpGhost);
	}
	for (auto& startRacePos : m_startRacePosList) {
		g_goMgr->DeleteGameObject(startRacePos);
	}
	g_goMgr->DeleteGameObject(m_bg);
	g_goMgr->DeleteGameObject(m_gc);
	
}
void Game::Update()
{
	for (int i = 0; i < 3; i++) {
		m_comPad[i].SetPosition(m_player[i+1]->GetPosition());
	}

}
void Game::Render()
{
}
