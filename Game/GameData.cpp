#include "stdafx.h"
#include "GameData.h"

void GameData::List_push_buck(int minute, int second,float comma, int PlayerNo)
{
	m_rankingList.push_back({minute, second, comma, PlayerNo });
}
void GameData::Init()
{
	//メモリ開放したい用（強制的にデストラクタ）
	std::vector<RankResult>().swap(m_rankingList);
	m_CharaNum = 0;
	m_goal     = false;
	m_playerState = true;
}