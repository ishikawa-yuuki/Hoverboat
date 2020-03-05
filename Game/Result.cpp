#include "stdafx.h"
#include "Result.h"
#include "GameData.h"
#include "Title.h"
Result::Result()
{
	m_gamedata = &GameData::GetInstance();

}
Result::~Result()
{
}
void Result::Update()
{

	if (g_pad->IsTrigger(enButtonA))
	{	//ƒ^ƒCƒgƒ‹‚Ö
		g_goMgr->NewGameObject<Title>();
		g_goMgr->DeleteGameObject(this);
	}

}
void Result::Render()
{

}