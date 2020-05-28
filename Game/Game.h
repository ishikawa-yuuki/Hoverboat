#pragma once
#include "GameObjectManager.h"
#include "level/Level.h"
#include "RenderTarget.h"
#include "SoundSource.h"
#include "PlayerPad.h"
#include "ComputerPad.h"
#include "CFont.h"
#include "Sprite.h"
class Back;
class RaceTimer;
class GameData;
class StartRacePos;
class CPSwitchG;
class CoursePass;
class WeekBackPass;
class GameCamera;
class Player;
class BackGround;
class Game : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Game();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Game();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender() override;
private:
	static const int gamePadSize = 4;				//ゲームパッド最大数
	Player* m_player[gamePadSize] = { nullptr };	//プレイヤー
	Back* m_back = nullptr;							//背景
	BackGround* m_bg = nullptr;						//ステージ
	GameCamera* m_gc = nullptr;						//ゲームカメラ
	GameData* m_gamedata = nullptr;					//ゲームデータ
	RaceTimer* m_raceTime = nullptr;				//レースタイム
	CSoundSource* m_bgm = nullptr;					//サウンド
	CFont m_font;									//フォント
	Sprite m_sprite;								//スプライト
	Sprite m_spriteButton;							//ボタンUI
	Sprite m_spriteButtonRB;						//ボタンUI2
	Sprite m_spriteTime;							//タイム用
	Sprite m_spriteStart;							//スタート用
	Level m_level;									//レベル
	PlayerPad m_playerPad;							//プレイヤー用のゲームパッド。
	ComputerPad m_comPad[3];						//AI用のゲームパッド。
	std::vector<CoursePass*> m_coursePassList;		//コースパス用
	std::vector<WeekBackPass*> m_weekbackPassList;	//周回計測用
	std::vector<CPSwitchG*> m_CPGhostList;			//AI用の当たり判定
	std::vector<StartRacePos*> m_startRacePosList;	//スタートポジション
	std::vector<CoursePass*> m_reStartPassList;     //落下した後復活するポジション
	std::vector<CoursePass*> m_deadZoneList;        //落下死判定用
	RenderTarget m_renderTarget;					//レンダリングターゲット。
	
};

