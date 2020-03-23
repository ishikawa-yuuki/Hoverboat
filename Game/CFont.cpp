#include "stdafx.h"
#include "CFont.h"
#include "util/Util.h"
DirectX::SpriteFont* FontFactory::Load(const wchar_t* path)
{

	int key = Util::MakeHash(path);

	if (m_fontmap.count(key) == 0) {

		//std::make_unique  スマートポインタ生成のヘルパー関数
		//newが不要になる、()に初期値
		m_fontmap.emplace(key, std::make_unique<DirectX::SpriteFont>(g_graphicsEngine->GetD3DDevice(), path));
	}

	//getでマッピングされている値
	return m_fontmap[key].get();
}

FontFactory CFont::m_fontfactory;
CFont::CFont()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();

	m_spriteFont = g_graphicsEngine->GetSpriteFont();

	m_screenSize.x = FRAME_BUFFER_W;

	m_screenSize.y = FRAME_BUFFER_H;

}

CFont::~CFont()
{
}

void CFont::Draw(
	wchar_t const* text,
	const CVector2& pos,
	const CVector4& color,
	const CVector2& scale,
	const CVector2& pivot,
	float rotation,
	DirectX::SpriteEffects effects,
	float layerDepth

) {
	DrawScreenPos(text, { pos.x * m_screenSize.x, pos.y * m_screenSize.y }, color, scale, pivot, rotation, effects, layerDepth);
}

void CFont::DrawScreenPos(
	wchar_t const* text,
	const CVector2& pos,
	const CVector4& color,
	const CVector2& scale,
	const CVector2& pivot,
	float rotation,
	DirectX::SpriteEffects effects,
	float layerDepth
)
{/*
	if (text == nullptr) {
		return;
	}
	layerDepth *= 0.999f; layerDepth += 0.001f;

	layerDepth -= g_graphicsEngine->AddAndGetLayerDepthCnt();*/

	/*ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

	ID3D11BlendState* blendState;

	float dummy[4];

	UINT dummy2;

	dc->OMGetBlendState(&blendState, dummy, &dummy2);*/

	g_graphicsEngine->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred/*, blendState*/);
	/*if (blendState != nullptr)
	{
		blendState->Release();
	}*/

	m_spriteFont->DrawString(

		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		DirectX::XMFLOAT2(scale.x, scale.y),
		effects,
		layerDepth
	);
	g_graphicsEngine->GetSpriteBatch()->End();

}