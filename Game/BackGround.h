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
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = {0.0f,-20.0f,0.0f};
};

