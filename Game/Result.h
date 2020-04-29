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
	CSoundSource* m_said = nullptr;						//�\�����B
	GameData* m_gamedata = nullptr;
	CFont m_font;
	Sprite m_sprite;
	bool m_open		= false;
	bool m_spriteX  = false;
	const float m_fontY = 150.0f;
	float m_row			= -70.0f;
	float m_count		= 0.0f;
	float m_scaleX		= 0.01f;
	float m_scaleY		= 0.01f;
	int m_rank			= 1;
};

