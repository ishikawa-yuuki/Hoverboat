#include "stdafx.h"
#include "Player.h"
#include "PlayerMove.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Player/Player_defult.cmo");
}


Player::~Player()
{
}

void Player::Update()
{
	playerMove.Update();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(playerMove.GetPlayerPosition(), CQuaternion::Identity(), CVector3::One());
}
void Player::Render()
{
	//�e�X�g(���C�g���񂷁j
	m_model.Update();

	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}