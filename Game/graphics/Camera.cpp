#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。
Camera g_camera2D;
void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	if (m_updateProjMatrixFunc == enUpdateProjMatrixFunc_Perspective) {
		//プロジェクション行列を計算。
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//画角。
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
			m_near,
			m_far
		);
	}
	else {
		m_projMatrix.MakeOrthoProjectionMatrix(m_width, m_height, m_near, m_far);
	}
	m_viewMatrixInv.Inverse(m_viewMatrix);
	m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
}