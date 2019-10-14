#pragma once
#include "GameObjectManager.h"
#include "Sprite.h"
#include "level/Level.h"
class Pass;
class Enemy;
class GameCamera;
class Player;
class BackGround;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Render();
private:
	Player* m_player = nullptr;
	BackGround* m_bg = nullptr;
	GameCamera* m_gc = nullptr;
	Enemy* m_enemy   = nullptr;
	Sprite m_sprite;
	Level m_level;
	std::vector<Pass*> m_passList;
};

