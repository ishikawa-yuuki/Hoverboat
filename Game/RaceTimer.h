#pragma once
#include "GameObjectManager.h"
#include "SoundSource.h"
#include "CFont.h"
class RaceTimer:public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RaceTimer();

	/// <summary>
    ///�@�f�X�g���N�^
    /// </summary>
	~RaceTimer();

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render() {};

	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender() override;

	/// <summary>
	/// �X�^�[�g�������m��֐�
	/// </summary>
	/// <returns></returns>
	bool GetRaceStart()
	{
		return m_raceStart;
	}
	void SetRaceStart()
	{
		m_raceStart = true;
	}
	//���擾
	int GetMinute()
	{
		return m_minute;
	}
	//�b�擾
	int GetSeond()
	{
		return m_second;
	}
	//�R���}�擾
	float GetComma()
	{
		return m_comma;
	}

private:
	CSoundSource* m_countSound = nullptr;   //�J�E���g�_�E���̉�
	CFont m_font;							//�t�H���g
	bool m_raceStart = false;				//���[�X�X�^�[�g�̔��f�p
	float m_count	 = 3.0f;				//�J�E���g����(�b)
	float m_timer	 = 0.0f;				//�^�C��
	float m_comma	 = 0.0f;				//�R���}
	int m_second	 = 0;					//�b
	int m_minute	 = 0;					//��
	
};

