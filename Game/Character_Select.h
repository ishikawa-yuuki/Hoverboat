#pragma once
#include "GameObjectManager.h"
#include "level/Level.h"
#include "Sprite.h"
class Player;
class GameData;
class Character_Select : public  IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Character_Select();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Character_Select();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	enum Chara {
		//�ŏ��l
		enState_First,
		Metal,
		Brick,
		Wood,
		//�ő�l
		enState_Last
	};
private:
	Chara m_selctChara = Metal;							//�L�����ԍ�
	Level m_level;										//���x��
	Sprite m_frame;										//�t���[��
	Sprite m_metal;										//UI
	Sprite m_brick;										
	Sprite m_wood;										
	SkinModel m_model;									//�w�i�B
	SkinModel m_modeldai;								//��
	GameData* m_gamedata = nullptr;						//�Q�[���f�[�^
	Player* m_player	 = nullptr;						//�v���C���[
	CVector3 m_metalPos = { -400.0f,200.0f,0.0f };		//UI�|�W�V����
	CVector3 m_brickPos = { -400.0f,100.0f,0.0f };		
	CVector3 m_woodPos  = { -400.0f,  0.0f,0.0f };		
	CVector3 m_framePos = m_metalPos;					//�t���[���̃|�W�V����
	CVector3 m_position = CVector3::Zero();				//�w�i�|�W�V����
	CVector3 m_posDai	= CVector3::Zero();				//��̃|�W�V����
	CVector3 m_scale	= CVector3::One();				//�w�i�傫��
	CVector3 m_scaledai = CVector3::One();				//��傫��
	CQuaternion m_rot	= CQuaternion::Identity();		//�w�i����
	float m_time		= 0.0f;							//�t���[���̈ړ��̐���
};

