#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//cmoファイル読み込み
	m_model.Init(L"Assets/modelData/Stage/Stage_defult.cmo");
	//静的物理オブジェクト生成
	m_static.CreateMeshObject(m_model,CVector3::Zero(), CQuaternion::Identity());
	m_model.SetShadowReciever(true);
	//ファイル名を使って、テクスチャをロードして、ShaderResourceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/Stage/Black.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_specMapSRV);
	//スペキュラマップ設定
	m_model.SetSpecularMap(m_specMapSRV);
}


BackGround::~BackGround()
{
}
void BackGround::Release()
{
	//当たり判定リリース
	m_static.Release();
}
void BackGround::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void BackGround::Render()
{
	//通常描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}