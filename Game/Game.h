#pragma once
#include "GameObjectManager.h"
#include "Sprite.h"
#include "level/Level.h"
#include "RenderTarget.h"
#include "PlayerPad.h"
#include "ComputerPad.h"
class CPSwitchG;
class Pass;
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
	Player* m_player[4]		   = { nullptr };
	BackGround* m_bg           =   nullptr;
	GameCamera* m_gc		   =   nullptr;
	PlayerPad m_playerPad;						//プレイヤー用のゲームパッド。
	ComputerPad m_comPad[3];					//cp用のゲームパッド。
	//Sprite m_sprite;
	Level m_level;
	std::vector<Pass*> m_passList;
	std::vector<CPSwitchG*> m_CPGhostList;
	RenderTarget m_renderTarget;			   //レンダリングターゲット。
};

