#pragma once
#include "GameObjectManager.h"
#include "level/Level.h"
#include "RenderTarget.h"
#include "PlayerPad.h"
#include "ComputerPad.h"
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
	Game();
	~Game();
	void Update();
	void Render();
private:
	static const int gamePadSize = 4;
	Player* m_player[gamePadSize] = { nullptr };
	BackGround* m_bg = nullptr;
	GameCamera* m_gc = nullptr;
	GameData* m_gamedata = nullptr;
	RaceTimer* m_raceTime = nullptr;
	Level m_level;
	PlayerPad m_playerPad;							//プレイヤー用のゲームパッド。
	ComputerPad m_comPad[3];						//AI用のゲームパッド。
	std::vector<CoursePass*> m_coursePassList;		//コースパス用
	std::vector<WeekBackPass*> m_weekbackPassList;	//周回計測用
	std::vector<CPSwitchG*> m_CPGhostList;			//AI用の当たり判定
	std::vector<StartRacePos*> m_startRacePosList;	//スタートポジション
	std::vector<CoursePass*> m_reStartPassList;     //落下した後復活するポジション
	std::vector<CoursePass*> m_deadZoneList;
	RenderTarget m_renderTarget;					//レンダリングターゲット。
	
};

