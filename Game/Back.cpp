#include "stdafx.h"
#include "Back.h"

Back::Back()
{
	m_model.Init(L"Assets/modelData/Stage/Back.cmo");
	m_model.SetShadowReciever(true);

}


Back::~Back()
{
}
void Back::Release()
{
}
void Back::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
}
void Back::Render()
{
	//m_model.Update();
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}