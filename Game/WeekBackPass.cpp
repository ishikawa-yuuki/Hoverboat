#include "stdafx.h"
#include "WeekBackPass.h"


WeekBackPass::WeekBackPass()
{
	m_ghost.CreateBox(
		m_position,
		m_rot,
		m_scale
	);
}


WeekBackPass::~WeekBackPass()
{
}
