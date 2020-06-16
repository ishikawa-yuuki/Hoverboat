#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//cmo�t�@�C���ǂݍ���
	m_model.Init(L"Assets/modelData/Stage/Stage_defult.cmo");
	//�ÓI�����I�u�W�F�N�g����
	m_static.CreateMeshObject(m_model,CVector3::Zero(), CQuaternion::Identity());
	m_model.SetShadowReciever(true);
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResourceView���쐬����B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/Stage/Black.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_specMapSRV);
	//�X�y�L�����}�b�v�ݒ�
	m_model.SetSpecularMap(m_specMapSRV);
}


BackGround::~BackGround()
{
}
void BackGround::Release()
{
	//�����蔻�胊���[�X
	m_static.Release();
}
void BackGround::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void BackGround::Render()
{
	//�ʏ�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}