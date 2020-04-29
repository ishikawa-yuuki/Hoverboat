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

	void InitPass()
	{
		m_over = false;
	}

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
	bool m_over	 = false;
	bool m_start = false;
	PhysicsGhostObject m_ghost;
	CVector3 m_position	= CVector3::Zero();
	CQuaternion m_rot	= CQuaternion::Identity();
	CVector3 m_scale	= CVector3::One();
};

