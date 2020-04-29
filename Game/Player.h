#pragma once
#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
#include "GameObjectManager.h"
class GameData;
class GamePad;
class CPSwitchG;
class CoursePass;
class WeekBackPass;
struct PlayerData {
	float accel;//加速度
	float friction;//摩擦度
	float sutearing;
};
class Player : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

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
	void Render();

	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();

	void Release();

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// ジャンプ処理
	/// </summary>
	void Jump();

	/// <summary>
	/// ゴースト判定処理
	/// </summary>
	void CheckGhost();

	/// <summary>
	/// 周回用ゴースト判定
	/// </summary>
	void CheckPass();

	void CheckCourcePass();
	void ReStartPass();
	void WeekBack();
	void HitDead();

	/// <summary>
	/// キャラのデータ、当たり判定
	/// </summary>
	void Data();
	void SetChara(const int& num)
	{
		m_charaNum = num;
	}

	/*!
	 *@breif   PlayerのPositionを設定。
	*/
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}

	/*!
	 *@brief	PlayerのPositionを取得。
	 */
	const CVector3& GetPosition()const
	{
		return m_position;
	}

	/*!
	 *@brief	PlayerのCQuaternionを取得。
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
	bool GetDead()
	{
		return m_isDead;
	}
	bool GetReStart()
	{
		return m_reStart;
	}
	int GetWeekBack()
	{
		return m_weekbackNum;
	}
	void SetReStart() {
		m_reStart = false;
	}
	/// <summary>
	/// ゴール判定
	/// </summary>
	/// <returns></returns>
	bool GetPlayerGoal()
	{
		return m_goal;
	}

	void SetPad(GamePad* gamePad)
	{
		m_gamePad = gamePad;
	}
	const std::vector<CPSwitchG*>& SetGhostObjectList(const std::vector<CPSwitchG*>& List)
	{
		m_cpGhostList = List;
		return m_cpGhostList;
	}
	const std::vector<CoursePass*>& SetPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_courcePassList = List;
		return m_courcePassList;
	}
	const std::vector<CoursePass*>& SetReStartPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_reStartPassList = List;
		return m_reStartPassList;
	}
	const std::vector<CoursePass*>& SetDeadZonePassObjectList(const std::vector<CoursePass*>& List)
	{
		m_deadZoneList = List;
		return m_deadZoneList;
	}
	const std::vector<WeekBackPass*>& SetWeekPassObjectList(const std::vector<WeekBackPass*>& List)
	{
		m_weekbackPassList = List;
		return m_weekbackPassList;
	}
private:
	//アニメーション
	enum HumanAnimationClip {
		enAnimationClip_test,
		enAnimationClip_num
	};
	//cmoファイルの読み込み。
	struct CharaPass {
		
		const wchar_t hope[256] = L"Assets/modelData/hover/Hope.cmo";
		const wchar_t rennga[256] = L"Assets/modelData/hover/rennga.cmo";
		const wchar_t wood[256] = L"Assets/modelData/hover/wood.cmo";
	};
	
	wchar_t m_name[256] = L"Assets/modelData/hover/Hope.cmo";
	AnimationClip m_animClip[enAnimationClip_num];
	Animation m_animation;
	SkinModel m_model;	//スキンモデル。
	CharacterController m_charaCon;
	CharaPass m_charaPass;
	std::vector<CoursePass*> m_courcePassList;
	std::vector<CoursePass*> m_reStartPassList;     //落下した後復活するポジション
	std::vector<CPSwitchG*> m_cpGhostList;
	std::vector<WeekBackPass*> m_weekbackPassList;
	std::vector<CoursePass*> m_deadZoneList;
	std::vector<bool> m_weekBackOver;
	std::vector<bool> m_reStartOver;
	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;
	PlayerData* m_playerData		  = nullptr;//キャラ事のパラメータ
	GamePad* m_gamePad	              = nullptr;			
	GameData* m_gamedata			  = nullptr;
	CVector3 m_position		 = CVector3::Zero();
	CVector3 m_moveSpeed	 = CVector3::Zero();
	CVector3 m_accel		 = CVector3::Zero();	//加速度
	CVector3 m_jump			 = CVector3::Zero();     //ジャンプの加速度
	CVector3 m_reStartPos	 = CVector3::Zero();
	CQuaternion m_reStartRot = CQuaternion::Identity();
	CQuaternion m_rot	     = CQuaternion::Identity();
	CQuaternion m_effectRot  = {0.0f,0.0f,90.0f,1.0f};
	float m_friction	 = 0.98f;   //摩擦度
	float m_movePower	 = 100.0f;	// 移動速度
	float m_jumpPower	 = 0.0f;
	float m_cooltime     = 0.0f;
	int m_passNum		 = 0;
	int m_weekbackNum	 = 0;
	int m_charaNum		 = 0;
	bool m_first		 = false;
	bool m_goal			 = false;
	bool m_one			 = false;
	bool m_isDead        = false;
	bool m_reStart		 = false;
	bool m_isJump		 = false;
	bool m_isTime		 = false;
	
};


