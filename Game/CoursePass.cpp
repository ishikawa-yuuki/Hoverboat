#include "stdafx.h"
#include "CoursePass.h"


CoursePass::CoursePass()
{
}


CoursePass::~CoursePass()
{
}
void CoursePass::Release()
{
	m_ghost.Release();
}
void CoursePass::Start() {
	//当たり判定生成(箱)
	m_ghost.CreateBox(
		m_position,
		m_rot,
		m_scale
	);
	m_start = true;
}
void CoursePass::Update()
{
	if (!m_start) {
		Start();
	}
};

