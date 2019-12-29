#include "stdafx.h"
#include "Enemy.h"
#include "Pass.h"
#include "GamePad.h"
Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/Player/Player_Defult.cmo");
	/*m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);*/
	m_ghost.CreateBox(
		m_position,
		CQuaternion::Identity(),
		{ 60.0f,40.0f,60.0f }
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
	//Œü‚«‚ð’²‚×‚ÄˆÚ“®ˆ—
	m_diff = m_passList[i]->GetPosition() - m_position;
	m_diff.y = 0.0f;
	if (m_gamePad->IsPressAccel())
	{
		float angle = m_ComDirection.x * m_diff.z - m_ComDirection.z * m_diff.x;
		if (angle < 0.1f) {
			m_ComDirection.x += m_diff.x / 0.1f;
			m_ComDirection.z = m_diff.z;
			m_ComDirection.Normalize();
		}
		if (angle > 0.1f) {
			m_ComDirection.x -= m_diff.x / 0.1f;
			m_ComDirection.z = m_diff.z;
			m_ComDirection.Normalize();
		}
		else {
			//m_ComDirection = m_diff;
		}
		m_accel = m_diff * m_movePower;
	}
	else {
		m_accel = CVector3::Zero();
	}
	
	//”ÍˆÍ‚ª‹·‚¢‚ç‚µ‚¢
    if (m_diff.LengthSq() < 30.0f * 30.0f && !m_passList[i]->GetPass()) {
		m_passList[i]->OverPass();

	}
	else if (m_passList[i]->GetPass())
	{
		
		i++;
	}
	m_moveSpeed += m_accel;
	m_position = m_moveSpeed;// *(1.0f / 60.0f);
}
void Enemy::Update()
{


	Move();
	/*m_charaCon.SetPosition(m_position);*/
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	m_ghost.SetPosition(m_position);
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