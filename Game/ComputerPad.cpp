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
	m_first = true;
	return true;
}
void ComputerPad::Rotation()
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
void ComputerPad::Move()
{
	if (i == m_passList.size()) {
		i = 0;
		for (int j = 0; j < m_passList.size(); j++) {
			m_passList[j]->InitPass();
		}
	}
	m_diff = m_passList[i]->GetPosition() - m_position;
	m_diff.y = 0.0f;

	if (m_diff.LengthSq() < 50.0f * 50.0f && !m_passList[i]->GetPass()) {
		m_passList[i]->OverPass();
	}
	else if (m_passList[i]->GetPass())
	{

		i++;
	}
	m_moveSpeed = m_diff;
	m_moveSpeed.Normalize();
	m_moveSpeed += m_moveSpeed * 2000.0f;
	
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
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void ComputerPad::Check()
{
	
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		ghostObj = m_cpGhostList[j]->GetGhost();

		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//éüÇÃPassÇÃï˚å¸ÇîªíËÇ∑ÇÈèÍèä

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
	Check();
	Rotation();
	Move();
	Jump();
	m_charaCon.SetPosition(m_position);
}