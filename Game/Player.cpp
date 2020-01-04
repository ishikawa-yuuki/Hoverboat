#include "stdafx.h"
#include "Player.h"
#include "PlayerPad.h"
#include "ComputerPad.h"
Player::Player()
{
	//cmoファイルの読み込み。
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
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void Player::Render()
{
	//テスト(ライトを回す）
	//m_model.Update();
	//シルエット描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Silhouette
	);
	//通常描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}