#pragma once
#include "GameObjectManager.h"
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
};

