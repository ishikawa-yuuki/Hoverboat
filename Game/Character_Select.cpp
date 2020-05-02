#include "stdafx.h"
#include "Character_Select.h"
#include "GameData.h"
#include "Player.h"
#include "Game.h"
Character_Select::Character_Select()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 30.0f, 600.0f });
	g_camera3D.SetTarget({ 0.0f, 20.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	g_camera3D.Update();
	m_gamedata = &GameData::GetInstance();
	m_gamedata->Init();
	//スプライト初期化
	m_frame.Init(L"Assets/sprite/Frame_Y.dds", 200, 110);
	m_metal.Init(L"Assets/sprite/METAL.dds", 160, 80);
	m_brick.Init(L"Assets/sprite/BRICK.dds", 160, 80);
	m_wood.Init(L"Assets/sprite/WOOD.dds", 160, 80);

	//モデル初期化
	m_model.Init(L"Assets/modelData/Select/back.cmo");
	m_modeldai.Init(L"Assets/modelData/Select/dai.cmo");
	m_level.Init(L"Assets/level/select.tkl", [&](LevelObjectData& objdata)
	{
			if (objdata.EqualObjectName(L"back")) {
				
				m_position = objdata.position;
				m_scale = objdata.scale;
				m_rot = objdata.rotation;
				return true;
			}
			else if (objdata.EqualObjectName(L"dai")) {
				m_posDai = objdata.position;
				m_scaledai = objdata.scale;
				return true;
			}

		return false;
	});
	m_player = g_goMgr->NewGameObject<Player>();
	CVector3 pos = m_posDai;
	pos.y += 20.0f;
	m_player->SetPosition(pos);
	m_metal.Update(m_metalPos, CQuaternion::Identity(), CVector3::One());
	m_brick.Update(m_brickPos, CQuaternion::Identity(), CVector3::One());
	m_wood.Update(m_woodPos, CQuaternion::Identity(), CVector3::One());
	Fade().FadeInS();
}
Character_Select::~Character_Select()
{
}

void Character_Select::Update()
{
	m_time += GameTime().GetFrameDeltaTime();
	if (g_pad->GetLStickYF() >=0.6f && m_time >=0.2f)
	{
		m_time = 0.0f;
		m_selctChara = Chara(m_selctChara - 1);
		if (m_selctChara == Chara(enState_First))
		{
			m_selctChara = Chara(Wood);
		}
		m_gamedata->SetCharaNum(m_selctChara - 1);
		m_player->Release();
		g_goMgr->DeleteGameObject(m_player);
		m_player = g_goMgr->NewGameObject<Player>();
		CVector3 pos = m_posDai;
		pos.y += 20.0f;
		m_player->SetPosition(pos);
	}
	else if(g_pad->GetLStickYF() <= -0.6f && m_time >=0.2f) {

		
		m_time = 0.0f;
		m_selctChara = Chara(m_selctChara + 1);
		if (m_selctChara == Chara(enState_Last))
		{
			m_selctChara = Chara(Metal);
		}
		m_gamedata->SetCharaNum(m_selctChara - 1);
		m_player->Release();
		g_goMgr->DeleteGameObject(m_player);
		m_player = g_goMgr->NewGameObject<Player>();
		CVector3 pos = m_posDai;
		pos.y += 20.0f;
		m_player->SetPosition(pos);
	}
	switch (m_selctChara)
	{
	case Metal:
		m_framePos = m_metalPos;
		break;
	case Brick:
		m_framePos = m_brickPos;
		break;
	case Wood:
		m_framePos = m_woodPos;
		break;
	}
	//決定
	if (g_pad->IsTrigger(enButtonA))
	{
		//ゲームへ
		m_gamedata->SetCharaNum(m_selctChara-1);
		Fade().SetAlpha(1.0f);
		m_player->Release();
		g_goMgr->DeleteGameObject(m_player);
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
		return;
	}
	
	m_frame.Update(m_framePos, CQuaternion::Identity(), CVector3::One());
	m_model.UpdateWorldMatrix(m_position, m_rot, m_scale);
	m_modeldai.UpdateWorldMatrix(m_posDai, CQuaternion::Identity(), m_scaledai);
}
void Character_Select::Render()
{
	//通常描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	m_modeldai.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
	//スプライト描画
	m_metal.Draw();
	m_brick.Draw();
	m_wood.Draw();
	m_frame.Draw();
}
