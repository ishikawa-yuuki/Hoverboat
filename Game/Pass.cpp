#include "stdafx.h"
#include "Pass.h"


Pass::Pass()
{
	m_ghost.CreateBox(
		m_position,
		CQuaternion::Identity(),
		{ 1000.0f,100.0f,1000.0f }
	);
}


Pass::~Pass()
{
}


