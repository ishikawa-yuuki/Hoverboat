#pragma once
#include "GameObjectManager.h"
#include "CFont.h"
class GameData;

class Result : public IGameObject
{
public:
	Result();
	~Result();
	void Update() ;
	void Render() ;
	void PostRender()override;

private:
	GameData* m_gamedata = nullptr;
	CFont m_font;
};

