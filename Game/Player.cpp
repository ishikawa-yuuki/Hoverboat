#include "stdafx.h"
#include "Player.h"
#include "CPSwitchG.h"
#include "WeekBackPass.h"
#include "PlayerPad.h"
#include "ComputerPad.h"
Player::Player()
{
	m_animClip[enAnimationClip_test].Load(L"Assets/animData/test.tka");
	m_animClip[enAnimationClip_test].SetLoopFlag(true);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/hover/Hope.cmo");
	/*m_model.PlayAnimation(enAnimationClip_test, 0.2);*/
	m_animation.Init(m_model, m_animClip, enAnimationClip_num);
	m_animation.Play(0,0.4f);
}


Player::~Player()
{
}
bool Player::Start()
{
	m_charaCon.Init(
		30.0f,
		20.0f,
		m_position
	);
	//m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_first = true;
	return true;
}
void Player::Rotation()
{
	m_gamePad->Rotation();
	CVector3 stick;
	stick.x = m_gamePad->GetLstickXF();
	m_rot = m_gamePad->GetRotation();
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
void Player::Move()
{
	m_gamePad->Move();
	if (m_gamePad->IsPressAccel())
	{
		
		m_accel = m_gamePad->GetDirection() * m_movePower;
	}
	else {
		m_accel = CVector3::Zero();
	}
	m_moveSpeed += m_accel;	//�������ւ̈ړ����x�����B
	m_moveSpeed *= m_friction;//���C
}
void Player::Jump()
{

	if (m_gamePad->IsPressJump() )
	{
		m_jump.y = 10.0f;
	}
	else {
		m_jump = CVector3::Zero();
		if (m_charaCon.IsOnGround()) {
			m_moveSpeed.y = 0.0f;
		}
		else
		{
			m_moveSpeed.y -= 100.0f;
		}
	}
	m_moveSpeed += m_jump * 5.0f;
}
void Player::CheckGhost()
{
	PhysicsGhostObject* ghostObj =nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		ghostObj = m_cpGhostList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//���񔻒肷��ꏊ
				m_gamePad->CheckGhost();
			}
		});
	}
}
void Player::CheckPass()
{
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		ghostObj = m_weekbackPassList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//���񔻒肷��ꏊ
				if (j == 0)
					WeekBack();
				else {
					m_weekbackPassList[j]->HitPass();
				}
			}
		});
	}
}
void Player::WeekBack()
{
	//�X�^�[�g�n�_�ɂĐ��Z
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		if (m_weekbackPassList[j]->GetPass()) {
			m_passNum++;
		}
		m_weekbackPassList[j]->InitPass();
	}
	if (m_passNum == m_weekbackPassList.size()-1)
	{
		m_passNum = 0;
		m_weekbackNum++;
	}
	
}
void Player::Update()
{
	if (!m_first) {
		Start();
		
	}
	if (m_gamePad != nullptr) 
	{
			Rotation();
			CheckGhost();

			Jump();
			Move();
			CheckPass();
		m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
	m_animation.Update(1.0f / 60.0f);
	m_charaCon.SetPosition(m_position);
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void Player::Render()
{
	//�e�X�g(���C�g���񂷁j
	//m_model.Update();
	//�V���G�b�g�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Silhouette
	);
	//�ʏ�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}