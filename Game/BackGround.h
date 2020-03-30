#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update();
	void Render();
	void Release();
private:
	SkinModel m_model;									//スキンモデル。
	SkinModel m_model2;									//スキンモデル。
	PhysicsStaticObject m_static;
};

