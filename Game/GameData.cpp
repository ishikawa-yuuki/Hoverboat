#include "stdafx.h"
#include "GameData.h"

void GameData::List_push_buck(float PlayerNo, float GoalTime)
{
	m_rankingList.push_back({PlayerNo, GoalTime});
}