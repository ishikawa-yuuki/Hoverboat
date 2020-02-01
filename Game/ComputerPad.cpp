#include "stdafx.h"
#include "ComputerPad.h"
#include "CoursePass.h"
#include "PhysicsGhostObject.h"
ComputerPad::ComputerPad()
{
}


ComputerPad::~ComputerPad()
{
}
bool ComputerPad::Start()
{

	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_cpDirection = m_courcePassList[i]->GetPosition() - m_position;
	m_cpDirection.y = 0.0f;
	m_cpDirection.Normalize();
	m_first = true;
	return true;
}
void ComputerPad::Rotation()
{
	float angle = atan2(m_cpDirection.x, m_cpDirection.z);
	m_rot.SetRotation(CVector3::AxisY(), angle);
}
void ComputerPad::Move()
{
	if (!m_first)
	{
		Start();
	}
	if (i == m_courcePassList.size()) {
		i = 0;
		for (int j = 0; j < m_courcePassList.size(); j++) {
			m_courcePassList[j]->InitPass();
		}
	}
	
	m_passDirection = m_courcePassList[i]->GetPosition() - m_position;
	;
	m_passDirection.y = 0.0f;
	if (m_passDirection.LengthSq() < 550.0f * 550.0f && !m_courcePassList[i]->GetPass()) {
		m_courcePassList[i]->OverPass();
	}
	else if (m_courcePassList[i]->GetPass())
	{
		i++;
	}
	if (m_stickL >= 0.0f || m_stickL <= 0.0f)
	{
		m_stickL *= 0.8f;
	}
}
void ComputerPad::Jump()
{
	/*if (m_charaCon.IsOnGround()) {
		m_moveSpeed.y = 0.0f;
	}
	else
	{
		m_moveSpeed.y -= 100.0f;
	}*/
	
}
void ComputerPad::CheckGhost()
{
	//ŽŸ‚ÌPass‚Ì•ûŒü‚ð”»’è‚·‚éêŠ
				
	float angle = m_cpDirection.x * m_passDirection.z - m_cpDirection.z * m_passDirection.x;
	if (angle == 0.0f)
	{
			
		m_stickL = 0.0f;
	}
	else if (angle < 0.6f)
	{
		m_stickL = 1.0f;
	}
	else if (angle > -0.6f)
	{
		m_stickL = -1.0f;
	}
	else if (angle < 0.4f)
	{
		m_stickL = 0.5f;
	}
	else if (angle > -0.4f)
	{
		m_stickL = -0.5f;
	}
	
	m_passDirection.Normalize();
	m_cpDirection = m_passDirection;
}