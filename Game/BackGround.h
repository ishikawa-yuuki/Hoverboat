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
	PhysicsStaticObject m_static;
};

