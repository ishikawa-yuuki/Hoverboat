#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
class WeekBackPass :public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WeekBackPass();

	/// <summary>
	///　デストラクタ
	/// </summary>
	~WeekBackPass();

	/// <summary>
	/// Updateの直前で呼ぶ開始処理
	/// </summary>
	void Start();

	/// <summary>
	/// 更新。
	/// </summary>
	void Update();

	void Render() {};
	/*!
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでゴーストオブジェクトを削除したい場合に呼び出してください。
		*/
	void Release();

	//CPの座標を設定
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}

	//CPの大きさを設定
	void SetScale(const CVector3& scale) {
		m_scale = scale*1000;
	}

	/// <summary>
	/// ゴースト(当たり判定)取得。
	/// </summary>
	/// <returns>ゴースト</returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}

	/// <summary>
	/// 初期化
	/// </summary>
	void InitPass()
	{
		m_over = false;
	}

	/// <summary>
	/// 接触時
	/// </summary>
	void  HitPass()
	{
		m_over = true;
	}

	/// <summary>
	/// パス通過判定
	/// </summary>
	bool GetPass()const
	{
		return m_over;
	}
private:
	bool m_over	 = false;							//パスを通過したかどうか
	bool m_start = false;							//Updateで一度だけ実行
	PhysicsGhostObject m_ghost;						//ゴースト(当たり判定)
	CVector3 m_position	= CVector3::Zero();			//ポジション
	CQuaternion m_rot	= CQuaternion::Identity();	//向き
	CVector3 m_scale	= CVector3::One();			//大きさ
};

