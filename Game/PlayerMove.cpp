#include "stdafx.h"
#include "PlayerMove.h"


bool PlayerMove::Start()
{
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);
	m_moveDirection.y = 0.0f;
	m_moveDirection.Normalize();
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_first = true;
	return true;
}

void PlayerMove::Rotation()
{
	CVector3 stick;
	CQuaternion qRot = CQuaternion::Identity();
	stick.x = g_pad[0].GetLStickXF();
	qRot.SetRotationDeg(CVector3::AxisY(), stick.x * 1.4f);
	m_rot.Multiply(qRot);
	

}
void PlayerMove::Move()
{
	m_cameraForward = g_camera3D.GetForward();
	//XZ平面での前方方向に変換する。
	m_cameraForward.y = 0.0f;
	m_cameraForward.Normalize();

	if (g_pad->IsPress(enButtonRB1))
	{
		m_moveDirection = m_cameraForward;
		m_accel = m_moveDirection * 100.0f;
	}
	else {
		m_accel = CVector3::Zero();
	}
	/*float angle = m_moveDirection.x * cameraForward.z - m_moveDirection.z * cameraForward.x;
	if (angle < 0.1f) {
		m_moveDirection.x += cameraForward.x / 0.1f;
		m_moveDirection.z = cameraForward.z;
		m_moveDirection.Normalize();
	}
	if (angle > 0.1f) {
		m_moveDirection.x -= cameraForward.x / 0.1f;
		m_moveDirection.z = cameraForward.z;
		m_moveDirection.Normalize();
	}
	else {
		m_moveDirection = cameraForward;
	}*/

	m_moveSpeed += m_accel;	//奥方向への移動速度を代入。
	m_moveSpeed *= 0.98f;		//摩擦
}
void PlayerMove::Jump()
{
	

	if (g_pad->IsPress(enButtonA) && m_over)
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
	}
	m_moveSpeed += m_jump * 50.0f;
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void PlayerMove::Update()
{
	if (!m_first) {
		Start();
	}
	Rotation();
	Move();
	Jump();
	m_charaCon.SetPosition(m_position);
}
