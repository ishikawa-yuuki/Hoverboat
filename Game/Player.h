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
	float accel;//加速度       4byte
	float friction;//摩擦度    4byte
	float sutearing;           //4byte
    char name[256];           //256byte
	char specpass[256];		 //256byte
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

	/// <summary>
	/// リスタート地点通過判定
	/// </summary>
	void ReStartPass();

	/// <summary>
	/// 周回カウント時処理
	/// </summary>
	void WeekBack();

	/// <summary>
	/// 落下判定
	/// </summary>
	void HitDead();

	/// <summary>
	/// キャラのデータ、当たり判定
	/// </summary>
	void Data();

	/// <summary>
	/// エフェクト追従
	/// </summary>
	void EffectFollowing();

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
	/*!
	 *@breif Playerの死んでいるかの取得。
	*/
	bool GetDead()
	{
		return m_isDead;
	}
	/*!
	 *@breif　Playerのリスタート時の情報取得用。
	*/
	bool GetReStart()
	{
		return m_reStart;
	}
	/*!
	 *@breif周回数取得
	*/
	int GetWeekBack()
	{
		return m_weekbackNum;
	}
	/*!
	 *@breifリスタート時の情報取得終了
	*/
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
	/// <summary>
	/// パッド取得
	/// </summary>
	/// <param name="gamePad"></param>
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
	wchar_t m_name[256] ;								//パスネーム
	wchar_t m_specName[256];							//スペキュラマップパス
	AnimationClip m_animClip[enAnimationClip_num];		//アニメーションクリップ
	Animation m_animation;								//アニメーション
	SkinModel m_model;									//スキンモデル。
	CharacterController m_charaCon;						//キャラクターコントローラー（コリジョン）
	std::vector<CoursePass*> m_courcePassList;			//コース通過判定用
	std::vector<CoursePass*> m_reStartPassList;			//落下した後復活するポジション
	std::vector<CPSwitchG*> m_cpGhostList;
	std::vector<WeekBackPass*> m_weekbackPassList;		//周回判定用
	std::vector<CoursePass*> m_deadZoneList;			//落下死用
	std::vector<bool> m_weekBackOver;					//判定に通過したかどうか
	std::vector<bool> m_reStartOver;					//判定に通過したかどうか
	Effekseer::Effect* m_sampleEffect = nullptr;		//エフェクト用
	Effekseer::Handle m_playEffectHandle = -1;
	PlayerData* m_playerData		  = nullptr;		//キャラ事のパラメータ
	GamePad* m_gamePad	              = nullptr;			
	GameData* m_gamedata			  = nullptr;
	CVector3 m_position		 = CVector3::Zero();		//ポジション
	CVector3 m_moveSpeed	 = CVector3::Zero();		//スピード
	CVector3 m_accel		 = CVector3::Zero();		//加速度
	CVector3 m_jump			 = CVector3::Zero();		//ジャンプの加速度
	CVector3 m_reStartPos	 = CVector3::Zero();		//リスタートポジション
	CQuaternion m_reStartRot = CQuaternion::Identity(); //リスタートの向き
	CQuaternion m_rot	     = CQuaternion::Identity(); //向き
	CQuaternion m_effectRot  = {0.0f,0.0f,90.0f,1.0f};  //エフェクトの向き
	const float m_radius       = 30.0f;			//当たり判定の半径
	const float m_height       = 20.0f;			//当たり判定の高さ
	const float m_gravity	   = 100.0f;		//重力
	const float m_frictionOver = 0.98f;			//摩擦最大
	const float m_frictionAdd  = 1.01f;			//緩やかな摩擦
	const float m_Addjump	   = 400.0f;		//ジャンプ力に乗算する値
	float m_friction	 = 0.98f;				//摩擦度
	float m_movePower	 = 100.0f;				// 移動速度
	float m_jumpPower	 = 0.0f;				//ジャンプ力
	float m_cooltime     = 0.0f;				//復活クールタイム
	int m_passNum		 = 0;					//通過したパスの数
	int m_weekbackNum	 = 0;					//周回数
	int m_charaNum		 = 0;					//キャラ番号
	bool m_first		 = false;				//Updateで一度だけ実行
	bool m_goal			 = false;				//ゴール用
	bool m_one			 = false;				//一度だけ通す用
	bool m_isDead        = false;				//死通知用
	bool m_reStart		 = false;				//リスタート用
	bool m_isJump		 = false;				//ジャンプ用
	bool m_isTime		 = false;				//復活中
	
	//todo  スペキュラマップ
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;
	//todo 法線マップ
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;

};


