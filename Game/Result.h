#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
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
	CSoundSource* m_said = nullptr;						//ï\é¶âπÅB
	GameData* m_gamedata = nullptr;
	CFont m_font;
};

