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
	void SetGoal()
	{
		m_goal = true;
	}
	bool GetGoal()
	{
		return m_goal;
	}
	void List_push_buck(float PlayerNo,float GoalTime);
	struct RankResult
	{
		float PlayerNo =0.0f;
		float GoalTime =0.0f;
	};
private:
	bool m_goal = false;
	std::vector<RankResult> m_rankingList;
};

