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
	////XZ平面での前方方向に変換する。
	m_cpDirection = m_courcePassList[m_passNum]->GetPosition() - m_position;
	m_cpDirection.y = 0.0f;
	m_cpDirection.Normalize();
	m_hitPass.resize(m_courcePassList.size());
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

	if (m_stickL >= 0.0f || m_stickL <= 0.0f)
	{
		m_stickL *= 0.8f;
	}

	//周回リセット
	if (m_passNum == m_courcePassList.size()) {
		m_passNum = 0;
		for (int j = 0; j < m_courcePassList.size(); j++) {
			m_hitPass[j] = false;
		}
	}
	
	m_passDirection = m_courcePassList[m_passNum]->GetPosition() - m_position;
	m_passDirection.y = 0.0f;

	//通過しなければ(true)に(true)なら次のパスへ
	if (m_passDirection.LengthSq() < 550.0f * 550.0f && !m_hitPass[m_passNum]) {
		m_hitPass[m_passNum] = true;
	}
	else if (m_hitPass[m_passNum])
	{
		m_passNum++;
	}
}
void ComputerPad::HitGhost()
{
	//次のPassの方向を判定する場所(外積)
				
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
void ComputerPad::HitCourcePass()
{
	if (!m_hitPass[m_passNum] && !m_hit)
		m_hitPass[m_passNum] = true;
		m_passNum++;
		m_hit =true;
}
void ComputerPad::NotHitPass()
{
	m_hit = false;
};