#include "stdafx.h"
#include "Player.h"
#include "PlayerMove.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Player/Player_Defult.cmo");
	//m_model.Init(L"Assets/modelData/unityChan.cmo");
}


Player::~Player()
{
}

void Player::Update()
{
	playerMove.Update();
	m_position = playerMove.GetPlayerPosition();
	m_rot = playerMove.GetPlayerRotation();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
}
void Player::Render()
{
	//�e�X�g(���C�g���񂷁j
	//m_model.Update();
	//�V���G�b�g�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		1
	);
	//�ʏ�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}