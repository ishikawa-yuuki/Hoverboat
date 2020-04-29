#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"

class CoursePass : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CoursePass();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CoursePass();

	/// <summary>
	/// Updateの直前で呼ぶ開始処理
	/// </summary>
	void Start();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void Render() {};
	void Release();
	/// <summary>
	/// Position設定
	/// </summary>
	/// <param name="pos">pos</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// Rotation設定
	/// </summary>
	/// <param name="rot">rot</param>
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}

	/// <summary>
	/// Scale設定
	/// </summary>
	/// <param name="scale">scale</param>
	void SetScale(const CVector3& scale) {
		m_scale = scale * 1000;
	}

	/// <summary>
	/// Position取得
	/// </summary>
	/// <returns>CoursePassのPosition</returns>
	CVector3 GetPosition()const
	{
		return m_position;
	}
	bool InitPass()
	{
		over = false;
		return over;
	}
	bool HitPass()
	{
		over = true;
		return over;
	}
	bool GetPass()const
	{
		return over;
	}
	PhysicsGhostObject* GetGhost()
	{
		return &m_ghost;
	}
private:
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
	PhysicsGhostObject m_ghost;  //ゴースト(当たり判定)
	bool over = false;
	bool m_start = false;
};

