#include "stdafx.h"
#include "CoursePass.h"


CoursePass::CoursePass()
{
	m_ghost.CreateBox(
		m_position,
		CQuaternion::Identity(),
		{ 1000.0f,100.0f,1000.0f }
	);
}


CoursePass::~CoursePass()
{
}


