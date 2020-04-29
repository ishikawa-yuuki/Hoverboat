#pragma once
#include "GameObjectManager.h"
/// <summary>
/// レーススタート地点クラス
/// </summary>
class StartRacePos : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StartRacePos();
	/// <summary>
	///　デストラクタ
	/// </summary>
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

