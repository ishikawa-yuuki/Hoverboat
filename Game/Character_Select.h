#pragma once
#include "GameObjectManager.h"
class Character_Select : public  IGameObject
{
	Character_Select();
	~Character_Select();
	void Update();
	void Render();
	void PostRender() override;
private:

};

