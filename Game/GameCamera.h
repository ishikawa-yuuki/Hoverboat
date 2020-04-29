#pragma once
#include "GameObjectManager.h"
class Player;
class GameData;
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCamera();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCamera();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render() {};

	/// <summary>
	/// player情報コピー
	/// </summary>
	void SetInfoPlayer(Player* pl)
	{
		m_player = pl;
	}
private:
	Player* m_player =nullptr;
	GameData* m_gamedata = nullptr;
	CVector3 m_target = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_rePosition = CVector3::Zero();
	CVector3 m_reTarget = CVector3::Zero();
	//注視点から視点までのベクトルを設定。
	CVector3 m_toCameraPos = { 0.0f, 0.0f, 400.0f };
	CVector3 m_retoCameraPos = m_toCameraPos;
	
};

