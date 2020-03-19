#include "stdafx.h"
#include "PlayerPad.h"

PlayerPad::PlayerPad()
{
}


PlayerPad::~PlayerPad()
{
} 
bool PlayerPad::Start()
{

	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_first = true;
	return true;
}
void PlayerPad::Rotation()
{
	CQuaternion qRot = CQuaternion::Identity();

	qRot.SetRotationDeg(CVector3::AxisY(), GetLstickXF());
	m_rot.Multiply(qRot);
}
void PlayerPad::Move()
{
	if (!m_first)
	{
		Start();
	}
	m_cameraForward = g_camera3D.GetForward();
	//XZïΩñ Ç≈ÇÃëOï˚ï˚å¸Ç…ïœä∑Ç∑ÇÈÅB
	m_cameraForward.y = 0.0f;
	m_cameraForward.Normalize();
	m_moveDirection = m_cameraForward;
}
void PlayerPad::Jump()
{


	/*if (IsPressJump() && m_over)
	{
		m_jump.y = 10.0f;
	}
	else {
		m_jump = CVector3::Zero();
		if (m_charaCon.IsOnGround()) {
			m_moveSpeed.y = 0.0f;
			m_over = true;
		}
		else
		{
			m_moveSpeed.y -= 100.0f;
		}
	}*/
	/*m_moveSpeed += m_jump * 5.0f;*/
}
void PlayerPad::HitCourcePass()
{

}
void PlayerPad::HitReStartPos()
{
	m_reStartRot = m_rot;
}
void PlayerPad::isDead()
{
	m_rot = m_reStartRot;
}