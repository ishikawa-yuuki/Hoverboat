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
	m_sprite.Init(L"Assets/sprite/fade.dds", g_graphicsEngine->Get2DSpaceScreenWidth(), g_graphicsEngine->Get2DSpaceScreenHeight());
	m_start = true;
}

void CFade::Update()
{
	if (!m_start) {
		Start();
	}
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 0.03f*GameTime().GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FideOut:
		m_currentAlpha += 0.03f*GameTime().GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:
		break;
	}
	/*m_a += 0.1*GameTime().GetFrameDeltaTime();
	m_currentAlpha = sin(m_a) * 0.5 + 0.5;*/
	/*m_currentAlpha = 1.0f;*/
	m_sprite.SetMulColor({ 1.0f,1.0f, 1.0f, m_currentAlpha });
}
void CFade::Render()
{
	
}
void CFade::PostRender()
{
	
	m_sprite.Draw();

}