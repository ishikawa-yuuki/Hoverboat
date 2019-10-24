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
	
	//�J�����̑O���������擾�B
	CVector3 cameraForward = g_camera3D.GetForward();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	//XZ�����̈ړ����x���N���A�B
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
	m_moveSpeed = cameraForward * m_movePower * m_movePress;	//�������ւ̈ړ����x�����B
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