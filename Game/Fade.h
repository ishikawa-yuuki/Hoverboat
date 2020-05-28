#pragma once
#include "Sprite.h"
class CFade
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CFade();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CFade();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
	void Start();
public:
	static CFade& GetInstance()
	{
		static CFade instance;
		return instance;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	///	�`��
	/// </summary>
	void Render();

	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender();

	//���X�ɖ��邭�Ȃ�B
	void FadeIn()
	{
		m_state = enState_FadeIn;
	}

	//���X�ɈÂ��Ȃ�B
	void FadeOut()
	{
		m_state = enState_FideOut;
	}

	//�������邭�Ȃ�B
	void FadeInS()
	{
		m_state = enState_FadeInS;
	}

	//�����Â��Ȃ�B
	void FadeOutS()
	{
		m_state = enState_FideOutS;
	}

	//Fade���
	bool IsFade() const {
		return m_state != enState_Idle;
	}

	//���l�l��
	float GetCurrentAlpha() const {
		return m_currentAlpha;
	}

	//���l�ݒ�
	void SetAlpha(float alpha)
	{
		m_currentAlpha = alpha;
	}

private:
	//�t�F�C�h���
	enum enState_Fade {
		enState_FadeIn,
		enState_FideOut,
		enState_FadeInS,
		enState_FideOutS,
		enState_Idle
	};
	Sprite m_sprite;						//�t�F�C�h�p�X�v���C�g
	enState_Fade m_state = enState_Idle;	//�t�F�C�h���
	bool m_start = false;					//Update�ň�x�������s
	float m_currentAlpha = 1.0f;			//���l
};
static inline CFade& Fade()
{
	return CFade::GetInstance();
}
