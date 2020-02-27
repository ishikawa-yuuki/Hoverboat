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
private:
	bool m_goal = false;
};

