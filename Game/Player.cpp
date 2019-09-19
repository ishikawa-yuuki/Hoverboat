#include "stdafx.h"
#include "Player.h"
#include "PlayerMove.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Player/Player_defult.cmo");
}


Player::~Player()
{
}

void Player::Update()
{
	playerMove.Update();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(playerMove.GetPlayerPosition(), CQuaternion::Identity(), CVector3::One());
}
void Player::Render()
{
	//テスト(ライトを回す）
	m_model.Update();

	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}