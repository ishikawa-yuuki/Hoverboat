#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
GameCamera::GameCamera()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 800.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(100000.0f);
	g_camera3D.Update();
	m_gamedata = &GameData::GetInstance();
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{
	if (m_gamedata->GetPose())
	{
		return;
	}
	if (m_player != nullptr) {
		m_target = m_player->GetPosition();
		float x = g_pad[0].GetLStickXF();                 //パッドの入力を使ってカメラを回す。
		CQuaternion qRot;        
		qRot.SetRotationDeg(CVector3::AxisY(), 1.4f * x); //Y軸周りの回転
		
		
		if (m_player->GetReStart()) {
			m_rePosition = m_position;
			m_reTarget = m_target;
			m_retoCameraPos = m_toCameraPos;
			m_player->SetReStart();
		}
		if (m_player->GetDead())
		{

			m_position = m_rePosition;
			m_target = m_reTarget;
			m_toCameraPos = m_retoCameraPos;
			return;
		}
		qRot.Multiply(m_toCameraPos);
		m_target.y += 180.0f;

		m_position = m_target + m_toCameraPos;
		g_camera3D.SetTarget(m_target);                  
		g_camera3D.SetPosition(m_position);
		g_camera3D.Update();
	}
}
