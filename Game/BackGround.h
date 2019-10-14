#pragma once
#include "GameObjectManager.h"
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Render();
private:
	SkinModel m_model;									//スキンモデル。
};

