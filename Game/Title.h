#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render();
	void PostRender() override;
private:
	CFont m_font;
	CSoundSource* m_bgm = nullptr;						//BGM�B
	CSoundSource* m_decided = nullptr;					//���艹
	const int m_add			= 3;						
	const int m_addPress	= 20;						
	const float m_sinWave	= 0.5;						//�T�C���̔g�̎w��
	float  m_color			= 1.0f;
	float m_timer			= 0.0f;
	float m_fontTimer		= 0.0f;
	bool m_trigger			= false;
	CVector2 m_pos			= { 550.0f,600.0f };
	CVector2 m_scale		= {2.0f,2.0f};
	
};

