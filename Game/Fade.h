#pragma once
#include "Sprite.h"
class CFade
{
private:
	CFade();
	~CFade();
	void Start();
public:
	static CFade& GetInstance()
	{
		static CFade instance;
		return instance;
	}
	void Update();
	void Render();
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
	bool IsFade() const {
		return m_state != enState_Idle;
	}
	//���l�l��
	float GetCurrentAlpha() const {
		return m_currentAlpha;
	}
	void SetAlpha(float alpha)
	{
		m_currentAlpha = alpha;
	}
private:
	enum enState_Fade {
		enState_FadeIn,
		enState_FideOut,
		enState_Idle
	};
	Sprite m_sprite;
	enState_Fade m_state = enState_Idle;
	bool m_start = false;
	//���l
	float m_currentAlpha = 1.0f;
	float m_a = 0.0f;
};
static inline CFade& Fade()
{
	return CFade::GetInstance();
}
