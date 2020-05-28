#include "stdafx.h"
#include "PlayerPad.h"

PlayerPad::PlayerPad()
{
}
PlayerPad::~PlayerPad()
{
} 

void PlayerPad::Start()
{
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_first = true;
}
void PlayerPad::Rotation()
{
	CQuaternion qRot = CQuaternion::Identity();

	qRot.SetRotationDeg(CVector3::AxisY(), GetLstickXF());
	m_rot.Multiply(qRot);
}
void PlayerPad::Move()
{
	//一度だけ実行する
	if (!m_first)
	{
		Start();
	}
	//カメラの前情報を取得。
	m_cameraForward = g_camera3D.GetForward();
	//XZ平面での前方方向に変換する。
	m_cameraForward.y = 0.0f;
	m_cameraForward.Normalize();
	m_moveDirection = m_cameraForward;
}
void PlayerPad::HitReStartPos()
{
	m_reStartRot = m_rot;
}
void PlayerPad::isDead()
{
	m_rot = m_reStartRot;
}