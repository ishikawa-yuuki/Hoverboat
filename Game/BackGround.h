#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
class BackGround : public IGameObject
{
public:
	/// <summary>
	///	コンストラクタ
	/// </summary>
	BackGround();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BackGround();

	/// <summary>
	///	更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render();
	void Release();
private:
	SkinModel m_model;									//スキンモデル。
	PhysicsStaticObject m_static;

	//todo  スペキュラマップ
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;
};

