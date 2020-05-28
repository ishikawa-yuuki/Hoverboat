#pragma once
#include "GamePad.h"
class CoursePass;
class ComputerPad : public GamePad
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComputerPad();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComputerPad();

	/// <summary>
	/// Updateの直前で呼ぶ開始処理
	/// </summary>
	bool Start();

	/// <summary>
   /// 回転処理
   /// </summary>
	void Rotation();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// ジャンプ処理
	/// </summary>
	void Jump() {};

	/// <summary>
	/// ゴースト(当たり判定)
	/// </summary>
	void HitGhost();

	void HitCourcePass();
	void HitReStartPos() {};
	void isDead() {};
	void NotHitPass();

	/// <summary>
	/// Lスティック取得
	/// </summary>
	float GetLstickXF()
	{
		return m_stickL;
	}

	/// <summary>
	/// アクセルボタン取得
	/// </summary>
	bool  IsPressAccel()
	{
		return m_pressAccel;
	}

	/// <summary>
	/// ジャンプボタン取得
	/// </summary>
	bool  IsPressJump()
	{
		return m_pressJump;
	}

	/// <summary>
	/// 向き取得
	/// </summary>
	CQuaternion GetRotation()
	{
		return m_rot;
	}

	/// <summary>
	/// 移動向き取得
	/// </summary>
	CVector3    GetDirection() { return m_cpDirection; }

	/// <summary>
	/// ポジション設定
	/// </summary>
	void SetPosition(CVector3 const& pos) { m_position = pos; }

	/// <summary>
	/// パスリストに情報を設定
	/// </summary>
	/// <param name="List">コースパスリスト</param>
	/// <returns></returns>
	const std::vector<CoursePass*>& SetPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_courcePassList = List;
		return m_courcePassList;
	}
private:
	std::vector<CoursePass*> m_courcePassList;				//コース通過判定用
	std::vector<bool> m_hitPass;							//パスヒット通知
	bool m_pressAccel		   = true;						//アクセルボタン
	bool m_pressJump		   = false;						//ジャンプボタン
	bool m_first			   = false;						//Updateで一度だけ実行
	bool m_hit				   = false;						//パスヒット通知制御
	float m_stickL			   = 0.0f;						//Lスティック
	int	  m_passNum		       = 0;							//通過済みパス番号
	CQuaternion m_rot		   = CQuaternion::Identity();	//向き
	CVector3 m_position		   = CVector3::Zero();			//ポジション
	CVector3 m_passDirection   = CVector3::Zero();			//Passの奥方向
	CVector3 m_cpDirection     = CVector3::Zero();			//Computerの奥方向
	
};

