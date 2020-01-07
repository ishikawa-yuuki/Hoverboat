#include "stdafx.h"
#include "CPSwitchG.h"


CPSwitchG::CPSwitchG()
{
	m_ghost.CreateBox(
		m_position,
		m_rot,
		{1300.0f,100.0f,2500.0f}
	);
}


CPSwitchG::~CPSwitchG()
{
}
