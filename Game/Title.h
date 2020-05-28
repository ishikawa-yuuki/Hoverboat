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

	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender() override;
private:
	Sprite m_sprite;									//�X�v���C�g
	CFont m_font;										//�t�H���g
	CSoundSource* m_bgm		= nullptr;					//BGM�B
	CSoundSource* m_decided = nullptr;					//���艹
	const int m_add			= 3;						//�T�C���J�[�u(�ɂ₩)
	const int m_addPress	= 20;						//�T�C���J�[�u(����)	
	const float m_sinWave	= 0.5;						//�T�C���̔g�̎w��
	float  m_color			= 1.0f;						//�J���[
	float m_timer			= 0.0f;						//�^�C��
	float m_fontTimer		= 0.0f;						//�t�H���g�^�C��
	float m_scale			= 2.0f;						//�傫��
	bool m_trigger			= false;					//�t�H���g�\���ؑ�
	CVector2 m_pos			= { -100.0f,-300.0f };		//�t�H���gpos

};

