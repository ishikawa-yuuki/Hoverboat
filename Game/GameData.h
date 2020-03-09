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
	void List_push_buck(float PlayerNo,float GoalTime);
	struct RankResult
	{
		float PlayerNo =0.0f;
		float GoalTime =0.0f;
	};
private:
	bool m_goal = false;
	bool m_pose = false;
	std::vector<RankResult> m_rankingList;
};

