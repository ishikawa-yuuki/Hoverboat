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
	//当たり判定生成(箱)
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