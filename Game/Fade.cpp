#include "stdafx.h"
#include "Fade.h"

CFade::CFade()
{
}


CFade::~CFade()
{
}

void CFade::Start()
{
	//初期化
	m_sprite.Init(L"Assets/sprite/fade.dds", g_graphicsEngine->Get2DSpaceScreenWidth(), g_graphicsEngine->Get2DSpaceScreenHeight());
	m_start = true;
}

void CFade::Update()
{
	if (!m_start) {
		Start();
	}
	//フェイド状態
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= m_loose *GameTime().GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FideOut:
		m_currentAlpha += m_loose *GameTime().GetFrameDeltaTime();
		if (m_currentAlpha >= m_One) {
			m_currentAlpha = m_One;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeInS:
		m_currentAlpha -= m_One * GameTime().GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FideOutS:
		m_currentAlpha += m_One * GameTime().GetFrameDeltaTime();
		if (m_currentAlpha >= m_One) {
			m_currentAlpha = m_One;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:
		break;
	}
	m_sprite.SetMulColor({ m_One,m_One, m_One, m_currentAlpha });
}
void CFade::Render()
{
}
void CFade::PostRender()
{
	
	m_sprite.Draw();

}