#include "stdafx.h"
#include "CPSwitchG.h"


CPSwitchG::CPSwitchG()
{
	m_ghost.CreateBox(
		m_position,
		m_rot,
		{1500.0f,100.0f,2400.0f}
	);
}


CPSwitchG::~CPSwitchG()
{
}
