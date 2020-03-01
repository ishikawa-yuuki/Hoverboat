#pragma once
#include "GameObjectManager.h"
class GameData;

class Result : public IGameObject
{
public:
	Result();
	~Result();
	void Update() ;
	void Render() ;

private:
	GameData* m_gamedata = nullptr;

};

