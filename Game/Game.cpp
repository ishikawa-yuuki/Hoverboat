#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
#include "StartRacePos.h"
#include "CPSwitchG.h"
#include "CoursePass.h"
#include "WeekBackPass.h"
#include "BackGround.h"
#include "Back.h"
#include "RenderTarget.h"
#include "ShadowMap.h"
#include "Result.h"
#include "RaceTimer.h"
Game::Game()
{	
	//ゲームデータ取得
	m_gamedata = &GameData::GetInstance();
	//レベルで設置した情報読み込み
	m_level.Init(L"Assets/level/Stage_defult.tkl", [&](LevelObjectData & objdata)
	{
		//ステージ
		if (objdata.EqualObjectName(L"Stage_Defult")) {
			m_bg = g_goMgr->NewGameObject<BackGround>();
			return true;
		}//背景
		else if (objdata.EqualObjectName(L"Back")) {
			m_back = g_goMgr->NewGameObject<Back>();
			return true;
		}//コースパス
		else if (objdata.EqualObjectName(L"coursePass")) {
			CoursePass* coursePass = g_goMgr->NewGameObject<CoursePass>();
			coursePass->SetPosition(objdata.position);
			coursePass->SetRotation(objdata.rotation);
			coursePass->SetScale(objdata.scale);
			m_coursePassList.push_back(coursePass);
			return true;
		}//リスタート用
		else if (objdata.EqualObjectName(L"ReStartPass")) {
			CoursePass* coursePass = g_goMgr->NewGameObject<CoursePass>();
			coursePass->SetPosition(objdata.position);
			coursePass->SetRotation(objdata.rotation);
			coursePass->SetScale(objdata.scale);
			m_reStartPassList.push_back(coursePass);
			return true;
		}//落下死用
		else if (objdata.EqualObjectName(L"DeadZone")) {
			CoursePass* coursePass = g_goMgr->NewGameObject<CoursePass>();
			coursePass->SetPosition(objdata.position);
			coursePass->SetRotation(objdata.rotation);
			coursePass->SetScale(objdata.scale);
			m_deadZoneList.push_back(coursePass);
			return true;
		}//周回用
		else if (objdata.EqualObjectName(L"WeekBackPass")) {
			WeekBackPass* weekbackPass = g_goMgr->NewGameObject<WeekBackPass>();
			weekbackPass->SetPosition(objdata.position);
			weekbackPass->SetScale(objdata.scale);
			m_weekbackPassList.push_back(weekbackPass);
			return true;
		}//当たり判定
		else if (objdata.EqualObjectName(L"Ghost")) {
			CPSwitchG* cpGhost = g_goMgr->NewGameObject<CPSwitchG>();
			cpGhost->SetPosition(objdata.position);
			cpGhost->SetRotation(objdata.rotation);
			cpGhost->SetScale(objdata.scale);
			m_CPGhostList.push_back(cpGhost);
			return true;
		}//スタート地点
		else if (objdata.EqualObjectName(L"StartRacePos")) {
			StartRacePos* startRacePos= g_goMgr->NewGameObject<StartRacePos>();
			startRacePos->SetPosition(objdata.position);
			m_startRacePosList.push_back(startRacePos);
			return true;
		}
		return false;
	});
	m_raceTime = g_goMgr->NewGameObject<RaceTimer>();
	m_gc = g_goMgr->NewGameObject<GameCamera>();
	//スプライト初期化
	m_sprite.Init(L"Assets/sprite/gure_Frame.dds", 150, 40);
	m_spriteButton.Init(L"Assets/sprite/batu.dds", 25,25);
	m_spriteButtonRB.Init(L"Assets/sprite/R1.dds", 30, 25);
	m_spriteTime.Init(L"Assets/sprite/Time.dds", 30, 30);
	m_spriteStart.Init(L"Assets/sprite/TimeCount.dds", 200, 100);

	//スプライトカラー
	m_sprite.SetMulColor(CVector4{ 1.0f,1.0f,1.0f,0.5f });
	m_spriteButton.SetMulColor(CVector4{ 1.0f,1.0f,1.0f,0.9f });
	m_spriteButtonRB.SetMulColor(CVector4{ 1.0f,1.0f,1.0f,0.9f });
	m_spriteStart.SetMulColor(CVector4{1.0f,1.0f,1.0f,0.89f});

	//BGM設定
	m_bgm = new CSoundSource();
	m_bgm->Init(L"Assets/sound/StageBGM.wav");
	m_bgm->Play(true);
	m_bgm->SetVolume(0.1f);

	//0番目はユーザーが操作するプレイヤー
	for (int i = 0; i < gamePadSize; i++) {
		m_player[i] = g_goMgr->NewGameObject<Player>();
		m_player[i]->SetPosition(m_startRacePosList[i]->GetPosition());
		m_player[i]->SetPassObjectList(m_coursePassList);
		m_player[i]->SetGhostObjectList(m_CPGhostList);
		m_player[i]->SetWeekPassObjectList(m_weekbackPassList);
		m_player[i]->SetReStartPassObjectList( m_reStartPassList);
		m_player[i]->SetDeadZonePassObjectList(m_deadZoneList);
	}
	m_player[0]->SetPad(&m_playerPad);

	//カメラにプレイヤー情報を送る。
	m_gc->SetInfoPlayer(m_player[0]);
	//1,2,3番目はコンピューターが操作するプレイヤー
	m_player[1]->SetPad(&m_comPad[0]);
	m_player[2]->SetPad(&m_comPad[1]);
	m_player[3]->SetPad(&m_comPad[2]);

	for (int i = 0; i < 3; i++) {
		m_comPad[i].SetPassObjectList(m_coursePassList);
	}
	
	//カメラ更新
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
	//フェイドイン
	Fade().FadeIn();
}


Game::~Game()
{
	
	
}
void Game::Update()
{
	//レーススタート前
	if (!m_raceTime->GetRaceStart())
	{
		
		m_gamedata->SetPose();
	}
	else {
		
		m_gamedata->SetCanselPose();
	}
	for (int i = 0; i < 3; i++) {
		m_comPad[i].SetPosition(m_player[i + 1]->GetPosition());
	}

	{
		//影更新
		g_goMgr->SetShadowTarget( m_player[0]->GetPosition());
		g_goMgr->SetShadowPos();

	}

	//ゴール順にリストに入れてる
	for (int i = 0; i < gamePadSize; i++) {
		if (m_player[i]->GetPlayerGoal()) {
			m_gamedata->List_push_buck(m_raceTime->GetMinute(),
										m_raceTime->GetSeond(),
										m_raceTime->GetComma(),
										i);
			if (i == 0) {
				m_gamedata->SetGoal();
			}
			
		}
	}
	if (m_gamedata->GetGoal()) {
		//リザルトへ
	
		Fade().SetAlpha(1.0f);
		for (auto& pl : m_player) {	
			pl->Release();
				g_goMgr->DeleteGameObject(pl);
		}
		/// <summary>
		/// physics関連でクラッシュ↓ghostobject
		/// 対処 : コリジョンを消してからDeleteGameObject
		/// </summary>
		for (auto& coursePass : m_coursePassList) {
			coursePass->Release();
			g_goMgr->DeleteGameObject(coursePass);
		}
		for (auto& coursePass : m_reStartPassList) {
			coursePass->Release();
			g_goMgr->DeleteGameObject(coursePass);
		}
		for (auto& coursePass : m_deadZoneList) {
			coursePass->Release();
			g_goMgr->DeleteGameObject(coursePass);
		}
		for (auto& weekbackPass : m_weekbackPassList) {
			weekbackPass->Release();
			g_goMgr->DeleteGameObject(weekbackPass);
		}
		for (auto& cpGhost : m_CPGhostList) {
			cpGhost->Release();
			g_goMgr->DeleteGameObject(cpGhost);
		}
		for (auto& startRacePos : m_startRacePosList) {
			g_goMgr->DeleteGameObject(startRacePos);
		}
		m_bg->Release();
		m_bgm->Release();
		g_goMgr->DeleteGameObject(m_raceTime);
		g_goMgr->DeleteGameObject(m_bg);
		g_goMgr->DeleteGameObject(m_gc);
		g_goMgr->DeleteGameObject(m_back);
		g_goMgr->DeleteGameObject(this);
		//リザルトへ
		g_goMgr->NewGameObject<Result>();
	}

	//スプライト更新
	m_sprite.Update(CVector3{-535.0f,-10.0f,0.0f}, CQuaternion::Identity(), CVector3::One());
	m_spriteButton.Update(CVector3{ -570.0f,-110.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_spriteButtonRB.Update(CVector3{ -570.0f,-60.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	m_spriteTime.Update(CVector3{-90.0f,340.0f,0.0f}, CQuaternion::Identity(), CVector3::One());
	if (!m_raceTime->GetRaceStart())
	{
		m_spriteStart.Update(CVector3{ -10.0f,30.0f,0.0f }, CQuaternion::Identity(), CVector3::One());
	}
	

}
void Game::Render()
{
	//スプライト描画
	if (!Fade().IsFade())
	{
		m_sprite.Draw();
		m_spriteButton.Draw();
		m_spriteButtonRB.Draw();
		m_spriteTime.Draw();
		if (!m_raceTime->GetRaceStart())
		{
			m_spriteStart.Draw();
		}
	}
}
void Game::PostRender()
{
	
	//フォント表示
	if (!Fade().IsFade())
	{
		//レース中計測用
		wchar_t output[6];
		wchar_t output2[9];
		wchar_t output3[12];
		wchar_t output4[5];
		swprintf_s(output, L"LAP  ");
		swprintf_s(output2, L" %X / %X", m_player[0]->GetWeekBack(), 3);
		swprintf_s(output3, L"Accelerator");
		swprintf_s(output4, L"Jump");
		m_font.Begin();
		m_font.Draw(output, { -600.0f,0.0f }, CVector4::Yellow(), 0.0f, 1.5f);
		m_font.Draw(output2, { -550.0f,0.0f }, CVector4::White(), 0.0f, 1.5f);
		m_font.Draw(output3, { -550.0f,-50.0f }, CVector4::White(), 0.0f, 1.2f);
		m_font.Draw(output4, { -550.0f,-100.0f }, CVector4::White(), 0.0f, 1.2f);
		m_font.End();
	}
}