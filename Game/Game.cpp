#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "Player.h"
#include "BackGround.h"
Game::Game()
{
	m_player =  g_goMgr.NewGameObject<Player>();
	m_bg     =  g_goMgr.NewGameObject<BackGround>();
}


Game::~Game()
{
	g_goMgr.DeleteGameObject(m_player);
	g_goMgr.DeleteGameObject(m_bg);
}
void Game::Update()
{

}
void Game::Render()
{

}
