#pragma once
/*!
 * @brief	ゲームデータクラス。
 */
class GameData
{
private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameData() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameData() {};
public:
	static GameData& GetInstance()
	{
		static GameData gamedata;
		return gamedata;
	}

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// ポーズ設定
	/// </summary>
	void SetPose()
	{
		m_pose = true;
	}

	/// <summary>
	/// ポーズキャンセル
	/// </summary>
	void SetCanselPose()
	{
		m_pose = false;
	}

	/// <summary>
	/// ポーズを取得
	/// </summary>
	/// <returns></returns>
	bool GetPose()
	{
		return m_pose;
	}

	/// <summary>
	/// ゴール設定
	/// </summary>
	void SetGoal()
	{
		m_goal = true;
	}

	/// <summary>
	/// Playerの状態を設定
	/// </summary>
	/// <param name="state">trueならPC,falseならNPC</param>
	void SetPlayerState(bool state)
	{
		m_playerState = state;
	}

	/// <summary>
	/// キャラ選択設定
	/// </summary>
	/// <param name="num">キャラ番号</param>
	void SetCharaNum(int num)
	{
		m_CharaNum = num;
	}

	/// <summary>
	/// キャラの番号取得
	/// </summary>
	/// <param name="charaNum">キャラの最大数</param>
	/// <returns>選択キャラ番号</returns>
	int GetCharaNum(int charaNum_MAX)
	{
		if (!m_playerState)
		{
			int charaRandam;
			charaRandam = rand() % charaNum_MAX;
			return charaRandam;
		}
		return m_CharaNum;
	}

	/// <summary>
	/// ゴール情報取得
	/// </summary>
	/// <returns></returns>
	bool GetGoal()
	{
		return m_goal;
	}

	/// <summary>
	/// 結果を格納する関数
	/// </summary>
	/// <param name="minute">分</param>
	/// <param name="second">秒</param>
	/// <param name="comma">コンマ</param>
	/// <param name="PlayerNo">キャラナンバー</param>
	void List_push_buck(int minute, int second, float comma, int PlayerNo);

	/// <summary>
	/// ゴール時の分取得
	/// </summary>
	/// <param name="i">キャラ番号</param>
	/// <returns></returns>
	int GetMinute(int i)
	{
		return m_rankingList[i].m_minute;
	}

	/// <summary>
	/// ゴール時の秒取得
	/// </summary>
	/// <param name="i">キャラ番号</param>
	/// <returns></returns>
	int GetSeond(int i)
	{
		return m_rankingList[i].m_second;
	}

	/// <summary>
	/// ゴール時のコンマ4取得
	/// </summary>
	/// <param name="i">キャラ番号</param>
	/// <returns></returns>
	float GetComma(int i)
	{
		return m_rankingList[i].m_comma;
	}

	/// <summary>
	/// 順位
	/// </summary>
	/// <param name="i">キャラ番号</param>
	/// <returns></returns>
	int GetNum(int i)
	{
		return m_rankingList[i].PlayerNo;
	}

	/// <summary>
	/// リストサイズ取得
	/// </summary>
	/// <returns></returns>
	int GetListSize()
	{
		return m_rankingList.size();
	}
	struct RankResult
	{
		int   m_minute = 0;		//分
		int	  m_second = 0;		//秒
		float m_comma  = 0.0f;	//コンマ
		int PlayerNo   = 0;		//プレイヤー番号

	};
private:
	std::vector<RankResult> m_rankingList;	//ランキングリスト
	bool m_goal		    = false;					//ゴール判定
	bool m_pose			= false;					//ポーズ状態
	bool m_playerState  = true;					    //NPCかPCか(trueがPC)
	int m_CharaNum		= 0;						//キャラ番号
};

