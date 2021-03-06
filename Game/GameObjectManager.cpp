#include "stdafx.h"
#include "GameObjectManager.h"
#include "ShadowMap.h"
GameObjectManager* g_goMgr = nullptr;

bool GameObjectManager::Start() {
	
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//Effekseerを初期化。
	InitEffekseer();

	m_first = true;
	return true;
}
void GameObjectManager::InitEffekseer()
{
	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());

}

void GameObjectManager::PreRender() {
	

	////シャドウマップにレンダリング
	m_shadowMap.RenderToShadowMap();

}
void GameObjectManager::ForwordRender() {
	//レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	g_graphicsEngine->ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	
}
void GameObjectManager::PostRender() {

	Fade().PostRender();
	//ポストエフェクトの描画。
	m_postEffect.Draw();

	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	g_graphicsEngine->ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	m_copyMainRtToFrameBufferSprite.Draw();
	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();


	
	GameTime().Draw();
	
	//登録されているゲームオブジェクトのポストレンダー呼ぶ。
	for (auto go : m_goList)
	{
		go->PostRender();
		
	}
	

	
}
void GameObjectManager::Update()
{
	if (!m_first) {
		Start();
	}
	{
		//Effekseerカメラ行列を設定。
	//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseerを更新。
		m_effekseerManager->Update();

//シャドウマップを更新。
		m_shadowMap.UpdateFromLightTarget(
			m_shadowMapPos,
			m_shadowMapTarget
		);

		//登録されているゲームオブジェクトの更新処理を呼ぶ。
		for (auto go : m_goList)
		{
			go->Update();
			Fade().Update();
		}
		//ポストエフェクトの更新。
		m_postEffect.Update();

//描画
		//フレームバッファののレンダリングターゲットをバックアップしておく。
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);
		//ビューポートもバックアップを取っておく。
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

	
	
//プリレンダリング。
		PreRender();
/// フォワードレンダリング(通常の描画だと考えてOK)
		ForwordRender();
//通常描画
		for (auto go : m_goList) {
			go->Render();
		}
		
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
		
// ポストレンダリング
		PostRender();
	}
	
	for (auto it = m_goList.begin();
		it != m_goList.end();)
	{
		if ((*it)->isRequestDelete())
		{
			delete* it;
			it = m_goList.erase(it);
		}
		else
		{
			it++;
		}
	}
}
