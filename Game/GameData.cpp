#include "stdafx.h"
#include "GameData.h"

void GameData::List_push_buck(float PlayerNo, float GoalTime)
{
	m_rankingList.push_back({PlayerNo, GoalTime});
}
void GameData::Init()
{
	//メモリ開放したい用（強制的にデストラクタ）
	std::vector<RankResult>().swap(m_rankingList);
	m_goal = false;
}