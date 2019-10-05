#pragma once
#include "GameObjectManager.h"
class Pass : public IGameObject
{
public:
	Pass();
	~Pass();
	void Update() {};
	void Render() {};
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	CVector3 GetPosition()const
	{
		return m_position;
	}
	bool OverOK()
	{
		over = true;
		return over;
	}
	bool GetOver()
	{
		return over;
	}
private:
	CVector3 m_position = CVector3::Zero();
	bool over = false;
};

