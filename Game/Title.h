#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "Sprite.h"
#include "CFont.h"
class Title:public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Title();
	/// <summary>
	///�@�f�X�g���N�^
	/// </summary>
	~Title();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	void PostRender() override;
private:
	Sprite m_sprite;
	CFont m_font;
	CSoundSource* m_bgm		= nullptr;					//BGM�B
	CSoundSource* m_decided = nullptr;					//���艹
	const int m_add			= 3;						
	const int m_addPress	= 20;						
	const float m_sinWave	= 0.5;						//�T�C���̔g�̎w��
	float  m_color			= 1.0f;
	float m_timer			= 0.0f;
	float m_fontTimer		= 0.0f;
	float m_scale			= 2.0f;
	bool m_trigger			= false;
	CVector2 m_pos			= { -100.0f,-300.0f };

};

