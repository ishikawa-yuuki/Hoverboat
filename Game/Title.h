#pragma once
#include "GameObjectManager.h"
#include "Sprite.h"
#include "SoundSource.h"
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render();
private:
	Sprite m_sprite;
	CSoundSource* m_bgm = nullptr;						//BGMÅB
};

