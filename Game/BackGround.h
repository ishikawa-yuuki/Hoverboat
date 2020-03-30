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
	SkinModel m_model;									//�X�L�����f���B
	SkinModel m_model2;									//�X�L�����f���B
	PhysicsStaticObject m_static;
};

