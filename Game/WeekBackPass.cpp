#include "stdafx.h"
#include "WeekBackPass.h"

WeekBackPass::WeekBackPass()
{
}
WeekBackPass::~WeekBackPass()
{
}
void WeekBackPass::Release()
{
	m_ghost.Release();
}
void WeekBackPass::Start() 
{
	//ìñÇΩÇËîªíËê∂ê¨(î†)
	m_ghost.CreateBox(
		m_position,
		m_rot,
		m_scale
	);
	m_start = true;
}
void WeekBackPass::Update()
{
	if (!m_start) {
		Start();
	}
};