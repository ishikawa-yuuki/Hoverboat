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
	Game();
	~Game();
	void Update();
	void Render();
	void PostRender() override;
private:
	static const int gamePadSize = 4;
	Player* m_player[gamePadSize] = { nullptr };
	Back* m_back = nullptr;
	BackGround* m_bg = nullptr;
	GameCamera* m_gc = nullptr;
	GameData* m_gamedata = nullptr;
	RaceTimer* m_raceTime = nullptr;
	CSoundSource* m_bgm = nullptr;
	CFont m_font;
	Sprite m_sprite;
	Sprite m_spriteButton;
	Sprite m_spriteButtonRB;
	Sprite m_spriteTime;
	Sprite m_spriteStart;
	Level m_level;
	PlayerPad m_playerPad;							//�v���C���[�p�̃Q�[���p�b�h�B
	ComputerPad m_comPad[3];						//AI�p�̃Q�[���p�b�h�B
	std::vector<CoursePass*> m_coursePassList;		//�R�[�X�p�X�p
	std::vector<WeekBackPass*> m_weekbackPassList;	//����v���p
	std::vector<CPSwitchG*> m_CPGhostList;			//AI�p�̓����蔻��
	std::vector<StartRacePos*> m_startRacePosList;	//�X�^�[�g�|�W�V����
	std::vector<CoursePass*> m_reStartPassList;     //���������㕜������|�W�V����
	std::vector<CoursePass*> m_deadZoneList;        //����������p
	RenderTarget m_renderTarget;					//�����_�����O�^�[�Q�b�g�B
	
};

