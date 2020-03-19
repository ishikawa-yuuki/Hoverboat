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
	PlayerPad m_playerPad;							//�v���C���[�p�̃Q�[���p�b�h�B
	ComputerPad m_comPad[3];						//AI�p�̃Q�[���p�b�h�B
	std::vector<CoursePass*> m_coursePassList;		//�R�[�X�p�X�p
	std::vector<WeekBackPass*> m_weekbackPassList;	//����v���p
	std::vector<CPSwitchG*> m_CPGhostList;			//AI�p�̓����蔻��
	std::vector<StartRacePos*> m_startRacePosList;	//�X�^�[�g�|�W�V����
	std::vector<CoursePass*> m_reStartPassList;     //���������㕜������|�W�V����
	std::vector<CoursePass*> m_deadZoneList;
	RenderTarget m_renderTarget;					//�����_�����O�^�[�Q�b�g�B
	
};

