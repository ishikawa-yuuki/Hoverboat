#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/Stage/Stage_defult.cmo");
	m_static.CreateMeshObject(m_model,CVector3::Zero(), CQuaternion::Identity());
	m_model.SetShadowReciever(true);

}


BackGround::~BackGround()
{
}
void BackGround::Release()
{
	m_static.Release();
}
void BackGround::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void BackGround::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}