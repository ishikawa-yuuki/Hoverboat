#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
}


Title::~Title()
{
}
void Title::Update() 
{
	if (g_pad->IsPressAnyKey()) 
	{
		g_goMgr->NewGameObject<Game>();
		g_goMgr->DeleteGameObject(this);
	}
}
void Title::Render()
{

}
