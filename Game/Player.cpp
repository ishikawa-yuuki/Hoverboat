#include "stdafx.h"
#include "Player.h"
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

void Player::Update()
{
	
	m_animation.Update(1.0f/60.0f);
	if (m_gamePad != nullptr) {
		m_gamePad->UpdatePad();
		m_position = m_gamePad->GetPosition();
		m_rot = m_gamePad->GetRotation();
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
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