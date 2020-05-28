#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
class BackGround : public IGameObject
{
public:
	/// <summary>
	///	�R���X�g���N�^
	/// </summary>
	BackGround();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BackGround();

	/// <summary>
	///	�X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render();
	void Release();
private:
	SkinModel m_model;									//�X�L�����f���B
	PhysicsStaticObject m_static;
};

