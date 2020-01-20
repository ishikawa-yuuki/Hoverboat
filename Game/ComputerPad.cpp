#include "stdafx.h"
#include "ComputerPad.h"
#include "CPSwitchG.h"
#include "Pass.h"
#include "PhysicsGhostObject.h"
ComputerPad::ComputerPad()
{
}


ComputerPad::~ComputerPad()
{
}
bool ComputerPad::Start()
{
	m_charaCon.Init(
		30.0f,
		20.0f,
		m_position
	);
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_cpDirection = m_passList[i]->GetPosition() - m_position;
	m_cpDirection.y = 0.0f;
	m_cpDirection.Normalize();
	m_first = true;
	return true;
}
void ComputerPad::Rotation()
{
	CVector3 stick;
	stick.x = GetLstickXF();
	float angle = atan2(m_cpDirection.x, m_cpDirection.z);
	m_rot.SetRotation(CVector3::AxisY(), angle);
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
	if (m_stickL >= 0.0f||m_stickL<=0.0f)
	{
		m_stickL *= 0.8f;
	}
}
void ComputerPad::Move()
{
	if (i == m_passList.size()) {
		i = 0;
		for (int j = 0; j < m_passList.size(); j++) {
			m_passList[j]->InitPass();
		}
	}
	m_passDirection = m_passList[i]->GetPosition() - m_position;
	m_passDirection.y = 0.0f;
	if (m_passDirection.LengthSq() < 400.0f * 400.0f && !m_passList[i]->GetPass()) {
		m_passList[i]->OverPass();
	}
	else if (m_passList[i]->GetPass())
	{
		m_stickL = 0.0f;
		i++;
	}
	m_accel = m_cpDirection * m_movePower;
	m_moveSpeed += m_accel;
	m_moveSpeed *= m_friction;		//ñÄéC
	
}
void ComputerPad::Jump()
{
	if (m_charaCon.IsOnGround()) {
		m_moveSpeed.y = 0.0f;
	}
	else
	{
		m_moveSpeed.y -= 100.0f;
	}
	
}
void ComputerPad::Check()
{
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		ghostObj = m_cpGhostList[j]->GetGhost();

		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//éüÇÃPassÇÃï˚å¸ÇîªíËÇ∑ÇÈèÍèä
				
				float angle = m_cpDirection.x * m_passDirection.z - m_cpDirection.z * m_passDirection.x;
				if (angle == 0)
				{
					m_stickL = 0.0f;
				}
				else if (angle < 0.4f) 
				{
					m_stickL = 1.0f;
				}
				else if (angle > 0.4f) 
				{
					m_stickL = -1.0f;
				}
				m_passDirection.Normalize();
				m_cpDirection = m_passDirection;
				
			
				
			}
		});
	}
}
void ComputerPad::UpdatePad()
{
	if(!m_first)
	{
		Start();
	}
	
	Rotation();
	Move();
	Jump();
	Check();
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_charaCon.SetPosition(m_position);
}