#include "GameObjectManager.h"
class Back : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Back();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Back();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	void Release() {};
private:
	SkinModel m_model;									//スキンモデル。
};

