#include "stdafx.h"
#include "PlayerPad.h"
#include "CPSwitchG.h"

PlayerPad::PlayerPad()
{
}


PlayerPad::~PlayerPad()
{
} 
bool PlayerPad::Start()
{
	m_charaCon.Init(
		30.0f,
		20.0f,
		m_position
	);
	m_moveDirection.y = 0.0f;
	m_moveDirection.Normalize();
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_first = true;
	return true;
}

void PlayerPad::Rotation()
{
	CVector3 stick;
	CQuaternion qRot = CQuaternion::Identity();
	stick.x = GetLstickXF();
	qRot.SetRotationDeg(CVector3::AxisY(), stick.x * 1.4f);
	m_rot.Multiply(qRot);
	if (fabsf(stick.x) >= 0.8f)
	{
		m_friction *= 0.999f;
	}
	else {
		m_friction *= 1.01f;
		if (m_friction >= 0.98f) {
			m_friction = 0.98f;
		}
	}

}
void PlayerPad::Move()
{
	m_cameraForward = g_camera3D.GetForward();
	//XZ���ʂł̑O�������ɕϊ�����B
	m_cameraForward.y = 0.0f;
	m_cameraForward.Normalize();

	if (IsPressAccel())
	{
		m_moveDirection = m_cameraForward;
		m_accel = m_moveDirection * m_movePower;
	}
	else {
		m_accel = CVector3::Zero();
	}

	m_moveSpeed += m_accel;	//�������ւ̈ړ����x�����B
	m_moveSpeed *= m_friction;		//���C
}
void PlayerPad::Jump()
{


	if (IsPressJump() && m_over)
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
	m_moveSpeed += m_jump * 5.0f;
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void PlayerPad::Check()
{

	PhysicsGhostObject* ghostObj =nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		ghostObj = m_cpGhostList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//���񔻒肷��ꏊ
				m_cpGhostList[j]->OverPass();
			}
		});
	}

}
void PlayerPad::UpdatePad()
{
	
		if (!m_first) {
			Start();
		}
		Rotation();
		Check();
		Move();
		Jump();
		m_charaCon.SetPosition(m_position);
	
}