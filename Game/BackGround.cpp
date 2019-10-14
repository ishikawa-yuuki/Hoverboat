#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/Stage/Stage_defult.cmo");
}


BackGround::~BackGround()
{
}
void BackGround::Update()
{
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}
void BackGround::Render()
{
	m_model.Update();
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}