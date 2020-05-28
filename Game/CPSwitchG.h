/*!
 *@brief	CPの方向転換用
			ゴーストオブジェクトクラス
 */

#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"

class CPSwitchG : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CPSwitchG();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CPSwitchG();

	/// <summary>
	/// Updateの直前で呼ぶ開始処理
	/// </summary>
	void Start(); 

	/// <summary>
	/// 更新
	/// </summary>
	void Update(); 

	/// <summary>
	/// 描画
	/// </summary>
	void Render() {};


	void Release();
	//CPの座標を設定
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//CPの回転を設定
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//CPの大きさを設定
	void SetScale(const CVector3& scale) {
		m_scale = scale*1000;
	}

	/// <summary>
	/// 当たり判定取得
	/// </summary>
	/// <returns></returns>
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}

	/// <summary>
	/// パス初期化
	/// </summary>
	/// <returns></returns>
	bool InitPass()
	{
		m_t = false;
		return m_t;
	}

	/// <summary>
	/// パス通過
	/// </summary>
	/// <returns></returns>
	bool OverPass()
	{
		m_t = true;
		return m_t;
	}

	/// <summary>
	///	パス情報取得
	/// </summary>
	/// <returns></returns>
	bool GetPass()const
	{
		return m_t;
	}
private:
	bool m_t = false;								//パス通過取得用
	bool m_start = false;							//一度だけ実行する用
	PhysicsGhostObject m_ghost;						//当たり判定
	CVector3 m_position = CVector3::Zero();			//ポジション
	CQuaternion m_rot = CQuaternion::Identity();	//向き
	CVector3 m_scale = CVector3::One();				//大きさ
};