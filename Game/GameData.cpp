#include "stdafx.h"
#include "GameData.h"

void GameData::List_push_buck(int minute, int second,float comma, int PlayerNo)
{
	m_rankingList.push_back({minute, second, comma, PlayerNo });
}
void GameData::Init()
{
	//�������J���������p�i�����I�Ƀf�X�g���N�^�j
	std::vector<RankResult>().swap(m_rankingList);
	m_CharaNum = 0;
	m_goal     = false;
	m_playerState = true;
}