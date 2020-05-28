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
	/// �R���X�g���N�^
	/// </summary>
	Game();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Game();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender() override;
private:
	static const int gamePadSize = 4;				//�Q�[���p�b�h�ő吔
	Player* m_player[gamePadSize] = { nullptr };	//�v���C���[
	Back* m_back = nullptr;							//�w�i
	BackGround* m_bg = nullptr;						//�X�e�[�W
	GameCamera* m_gc = nullptr;						//�Q�[���J����
	GameData* m_gamedata = nullptr;					//�Q�[���f�[�^
	RaceTimer* m_raceTime = nullptr;				//���[�X�^�C��
	CSoundSource* m_bgm = nullptr;					//�T�E���h
	CFont m_font;									//�t�H���g
	Sprite m_sprite;								//�X�v���C�g
	Sprite m_spriteButton;							//�{�^��UI
	Sprite m_spriteButtonRB;						//�{�^��UI2
	Sprite m_spriteTime;							//�^�C���p
	Sprite m_spriteStart;							//�X�^�[�g�p
	Level m_level;									//���x��
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

