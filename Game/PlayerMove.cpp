#include "stdafx.h"
#include "PlayerMove.h"


bool PlayerMove::Start()
{
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);
	m_first = true;
	return true;
}
void PlayerMove::Update()
{
	if (!m_first) {
		Start();
	}
	
	m_position.x += g_pad[0].GetLStickXF()*2.0f;
	m_position.z += g_pad[0].GetLStickYF()*2.0f;
	m_charaCon.SetPosition(m_position);
}
