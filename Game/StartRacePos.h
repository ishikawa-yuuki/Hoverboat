#pragma once
#include "GameObjectManager.h"
/// <summary>
/// レーススタート地点クラス
/// </summary>
class StartRacePos : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StartRacePos();
	/// <summary>
	///　デストラクタ
	/// </summary>
	~StartRacePos();

	/// <summary>
	/// 更新
	/// </summary>
	void Update() {};

	/// <summary>
	/// 描画
	/// </summary>
	void Render() {};

	/// <summary>
	/// ポジション設定
	/// </summary>
	/// <param name="pos">ポジション</param>
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}

	/// <summary>
	/// ポジション取得
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition()const
	{
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero(); //スタートポジション
};

