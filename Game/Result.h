#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
#include "Sprite.h"
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
	Sprite m_sprite;
	bool m_open = false;
	bool m_spriteX = false;
	int m_rank = 1;
	const float m_fontY = 150.0f;
	float m_row = -70.0f;
	float m_count = 0.0f;
	float m_scaleX = 0.01f;
	float m_scaleY = 0.01f;
};

