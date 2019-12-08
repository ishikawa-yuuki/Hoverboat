#pragma once
#include "GameObjectManager.h"
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render();
};

