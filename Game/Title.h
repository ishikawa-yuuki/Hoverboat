#pragma once
#include "GameObjectManager.h"
#include "Sprite.h"
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render();
private:
	Sprite m_sprite;
};

