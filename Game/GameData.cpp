#include "stdafx.h"
#include "GameData.h"

void GameData::List_push_buck(float PlayerNo, float GoalTime)
{
	m_rankingList.push_back({PlayerNo, GoalTime});
}
void GameData::Init()
{
	//�������J���������p�i�����I�Ƀf�X�g���N�^�j
	std::vector<RankResult>().swap(m_rankingList);
	m_goal = false;
}