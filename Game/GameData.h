#pragma once
/*!
 * @brief	ゲームデータクラス。
 */
class GameData
{
private:
	GameData() {};
	~GameData() {};
public:
	static GameData& GetInstance()
	{
		static GameData gamedata;
		return gamedata;
	}
	void Init();
	//とりあえずここにPose
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
	bool GetGoal()
	{
		return m_goal;
	}
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
		float m_comma = 0.0f;
		int PlayerNo = 0.0f;

	};
private:
	bool m_goal = false;
	bool m_pose = false;
	std::vector<RankResult> m_rankingList;
};

