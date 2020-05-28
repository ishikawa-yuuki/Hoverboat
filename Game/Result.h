#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
#include "Sprite.h"
class GameData;
class Result : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Result();

	/// <summary>
	///�@�f�X�g���N�^
	/// </summary>
	~Result();

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	void PostRender()override;

private:
	CSoundSource* m_said = nullptr;		//�\�����B
	GameData* m_gamedata = nullptr;		//�Q�[���f�[�^				
	CFont m_font;						//���U���g�t�H���g
	Sprite m_sprite;					//�X�v���C�g
	bool m_open		= false;			//���U���g�\����
	bool m_spriteX  = false;			//�X�v���C�g�\���̍ۂ̕\���p
	const float m_fontY = 150.0f;		//�t�H���gpos
	float m_row			= -70.0f;		//�t�H���gpos
	float m_count		= 0.0f;			//�T�C���J�[�u
	float m_scaleX		= 0.01f;		//X�̃X�P�[��
	float m_scaleY		= 0.01f;		//Y�̃X�P�[��
	int m_rank			= 1;			//�����N
};

