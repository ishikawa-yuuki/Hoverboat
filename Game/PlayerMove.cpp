#include "stdafx.h"
#include "PlayerMove.h"


bool PlayerMove::Start()
{
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_moveSpeed
	);
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_first = true;
	return true;
}

void PlayerMove::Rotation()
{
	CVector3 stick;
	CQuaternion qRot = CQuaternion::Identity();
	stick.x = g_pad[0].GetLStickXF();
	qRot.SetRotationDeg(CVector3::AxisY(), stick.x * 1.0f);
	m_rot.Multiply(qRot);
	
	

}
void PlayerMove::Move()
{
	
	//カメラの前方方向を取得。
	CVector3 cameraForward = g_camera3D.GetForward();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	if (g_pad->IsPress(enButtonRB1))
	{
		
		if (m_movePress < 2.0f) {
			m_movePress += 0.5f;
		}
		else {
			m_movePress = 2.0f;
		}
	}
	else {
		if (m_movePress > 0.0f) {
			m_movePress -= 0.04f;
		}
		else
		{
			m_movePress = 0.0f;
		}
		/*m_moveVector = m_moveSpeed;*/
	}
	m_moveSpeed = cameraForward * m_movePower * m_movePress;	//奥方向への移動速度を代入。
	/*m_moveSpeed = (m_moveSpeed-m_moveVector)*m_moveForceMultiplier;*/
	m_position = m_charaCon.Execute(1.0f/60.0f,m_moveSpeed);
}
void PlayerMove::Update()
{
	if (!m_first) {
		Start();
	}
	Move();
	Rotation();

	m_charaCon.SetPosition(m_position);
}