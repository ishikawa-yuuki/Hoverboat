#pragma once
#include "GameObjectManager.h"
class StartRacePos : public IGameObject
{
public:
	StartRacePos();
	~StartRacePos();
	void Update() {};
	void Render() {};
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	const CVector3& GetPosition()const
	{
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero();
};

