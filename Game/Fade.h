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
	//徐々に明るくなる。
	void FadeIn()
	{
		m_state = enState_FadeIn;
	}
	//徐々に暗くなる。
	void FadeOut()
	{
		m_state = enState_FideOut;
	}
	//早く明るくなる。
	void FadeInS()
	{
		m_state = enState_FadeInS;
	}
	//早く暗くなる。
	void FadeOutS()
	{
		m_state = enState_FideOutS;
	}
	//Fade状態
	bool IsFade() const {
		return m_state != enState_Idle;
	}
	//α値獲得
	float GetCurrentAlpha() const {
		return m_currentAlpha;
	}
	//α値設定
	void SetAlpha(float alpha)
	{
		m_currentAlpha = alpha;
	}
private:
	enum enState_Fade {
		enState_FadeIn,
		enState_FideOut,
		enState_FadeInS,
		enState_FideOutS,
		enState_Idle
	};
	Sprite m_sprite;
	enState_Fade m_state = enState_Idle;
	bool m_start = false;
	//α値
	float m_currentAlpha = 1.0f;
};
static inline CFade& Fade()
{
	return CFade::GetInstance();
}
