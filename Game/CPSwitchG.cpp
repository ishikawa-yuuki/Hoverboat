#include "stdafx.h"
#include "CPSwitchG.h"


CPSwitchG::CPSwitchG()
{
}


CPSwitchG::~CPSwitchG()
{
}
void CPSwitchG::Release()
{
	m_ghost.Release();
}
void CPSwitchG::Start() {
	//当たり判定作成
	m_ghost.CreateBox(
		m_position,
		m_rot,
		m_scale
	);
	m_start = true;
}
void CPSwitchG::Update()
{
	if (!m_start) {
		Start();
	}

};
