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

	void SetPose()
	{
		m_pose = true;
	}

	void SetCanselPose()
	{
		m_pose = false;
	}

	bool GetPose()
	{
		return m_pose;
	}

	void SetGoal()
	{
		m_goal = true;
	}

	void SetCharaNum(int num)
	{
		m_CharaNum = num;
	}

	int GetCharaNum()
	{
		return m_CharaNum;
	}

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

	int GetMinute(int i)
	{
		return m_rankingList[i].m_minute;
	}
	int GetSeond(int i)
	{
		return m_rankingList[i].m_second;
	}
	float GetComma(int i)
	{
		return m_rankingList[i].m_comma;
	}
	int GetNum(int i)
	{
		return m_rankingList[i].PlayerNo;
	}
	int GetListSize()
	{
		return m_rankingList.size();
	}
	struct RankResult
	{
		int   m_minute = 0;
		int	  m_second = 0;
		float m_comma  = 0.0f;
		int PlayerNo   = 0;

	};
private:
	std::vector<RankResult> m_rankingList;
	bool m_goal    = false;
	bool m_pose	   = false;
	int m_CharaNum = 0;
};

