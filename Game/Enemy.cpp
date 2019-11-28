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
	if (i==m_passList.size()) {
		i = 0;
		for (int j = 0; j < m_passList.size(); j++) {
			m_passList[j]->InitPass();
		}
	}
	m_diff = m_passList[i]->GetPosition() - m_position;
	m_diff.y = 0.0f;
	//�͈͂������炵��
    if (m_diff.LengthSq() < 30.0f * 30.0f && !m_passList[i]->GetPass()) {
		m_passList[i]->OverPass();
	}
	else if (m_passList[i]->GetPass())
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


	/*Move();*/
	m_charaCon.SetPosition(m_position);
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), {2.0f,2.0f,5.0f});
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void Enemy::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);

}