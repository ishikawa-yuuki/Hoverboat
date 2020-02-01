#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 800.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	g_camera3D.Update();
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{

	if (m_player != nullptr) {
		m_target = m_player->GetPosition();
		float x = g_pad[0].GetLStickXF();                 //�p�b�h�̓��͂��g���ăJ�������񂷁B
		CQuaternion qRot;                                //Y������̉�]
		qRot.SetRotationDeg(CVector3::AxisY(), 1.4f * x);
		qRot.Multiply(m_toCameraPos);
	    m_position = m_target + m_toCameraPos;
		g_camera3D.SetTarget(m_target);                  
		g_camera3D.SetPosition(m_position);
		g_camera3D.Update();
	}
}
