#include "stdafx.h"
#include "Player.h"
#include "PlayerPad.h"
#include "ComputerPad.h"
Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Player/Player_Defult.cmo");
}


Player::~Player()
{
}

void Player::Update()
{
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