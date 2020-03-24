#include "stdafx.h"
#include "CFont.h"
CFont::CFont()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_spriteFont = g_graphicsEngine->GetSpriteFont();
	auto& ge = g_graphicsEngine;
	m_scaleMat.MakeScaling(
		{
			ge->GetFrameBufferWidth() / static_cast<float>(ge->Get2DSpaceScreenWidth()),
			ge->GetFrameBufferHeight() / static_cast<float>(ge->Get2DSpaceScreenHeight()),
			1.0f
		}
	);
}
CFont::~CFont()
{
}

void CFont::Begin()
{
	auto& ge = g_graphicsEngine;
	//レンダリングステートを退避させる。
	ge->PushRenderState();

	m_spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}
void CFont::End()
{
	auto& ge = g_graphicsEngine;
	m_spriteBatch->End();
	//レンダリングステートを復活させる。
	ge->PopRenderState(true);
}
void CFont::Draw(
	wchar_t const* text,
	const CVector2& position,
	const CVector4& color,
	float rotation,
	float scale,
	CVector2 pivot)
{
	if (text == nullptr) {
		return;
	}
	pivot.y = 1.0f - pivot.y;
	DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
	//座標系をスプライトと合わせる。
	CVector2 pos = position;
	float frameBufferHalfWidth = g_graphicsEngine->Get2DSpaceScreenWidth() * 0.5f;
	float frameBufferHalfHeight = g_graphicsEngine->Get2DSpaceScreenHeight() * 0.5f;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;

	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);
}