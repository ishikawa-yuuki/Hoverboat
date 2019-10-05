#include "stdafx.h"
#include "Enemy.h"
#include "Pass.h"

Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/Player/Player_Defult.cmo");
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);
}


Enemy::~Enemy()
{
}
void Enemy::Move()
{
	//if (i==3) {
	//	i = 0;
	//}
		m_diff = m_passList[i]->GetPosition() - m_position;
		m_diff.y = 0.0f;
		
		 if (m_diff.LengthSq() < 5.0f * 5.0f && m_passList[i]->GetOver() ==false) {
			m_passList[i]->OverOK();
		}
		else if (m_passList[i]->GetOver() )
		{
			i++;
		}
		m_moveSpeed = m_diff;
		m_moveSpeed.Normalize();
		m_moveSpeed += m_moveSpeed * 2000.0f;
		m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Enemy::Update()
{


	Move();
	m_charaCon.SetPosition(m_position);
	m_model.UpdateWorldMatrix(m_position,CQuaternion::Identity(),CVector3::One());
}
void Enemy::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}