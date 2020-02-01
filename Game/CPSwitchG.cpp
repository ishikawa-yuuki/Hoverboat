#include "stdafx.h"
#include "CPSwitchG.h"


CPSwitchG::CPSwitchG()
{
	m_ghost.CreateBox(
		m_position,
		m_rot,
		m_scale
	);
}


CPSwitchG::~CPSwitchG()
{
}
