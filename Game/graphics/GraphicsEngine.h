#pragma once
#include <stack>

/// <summary>
/// レンダリングモード。
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_Silhouette,		//シルエットレンダリング。
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};
class RenderTarget;
/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();

	/// <summary>
		/// フレームバッファの幅を取得。
		/// </summary>
	int GetFrameBufferWidth() const
	{
		return m_2dSpaceScreenWidth;
	}
	/// <summary>
	/// フレームバッファの高さを取得。
	/// </summary>
	int GetFrameBufferHeight() const
	{
		return m_2dSpaceScreenHeight;
	}

	/// <summary>
		/// 2D空間のスクリーンの幅を取得。
		/// </summary>
	int Get2DSpaceScreenWidth() const
	{
		return m_2dSpaceScreenWidth;
	}
	/// <summary>
	/// 2D空間のスクリーンの高さを取得。
	/// </summary>
	int Get2DSpaceScreenHeight() const
	{
		return m_2dSpaceScreenHeight;
	}

	/// <summary>
		/// 現在のレンダリングステートをスタックにプッシュ。
		/// </summary>
	void PushRenderState()
	{
		m_renderStateStack.push(m_currentRenderState);
	}
	/// <summary>
	/// スタックに退避したレンダリングステートをポップ。
	/// </summary>
	/// <param name="isApplyRenderState">
	/// ポップしたレンダリングステートをレンダリングパイプラインに設定するかどうかのフラグ。
	/// </param>
	void PopRenderState(bool isSetRenderStateToRenderPipeline)
	{
		m_currentRenderState = m_renderStateStack.top();
		m_renderStateStack.pop();
		if (isSetRenderStateToRenderPipeline == true) {
			m_pd3dDeviceContext->OMSetBlendState(m_currentRenderState.blendState, 0, 0xFFFFFFFF);
			m_pd3dDeviceContext->RSSetState(m_currentRenderState.rasterrizerState);
			m_pd3dDeviceContext->OMSetDepthStencilState(m_currentRenderState.depthStencilState, 0);
		}
	}
	//Sprite取得
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}

	//デフォルトフォント取得
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}
	/// <summary>
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
private:
	/// <summary>
		/// 各種レンダリングステート。
		/// </summary>
	struct SRenderState {
		ID3D11DepthStencilState* depthStencilState = nullptr;	//!<現在のデプスステンシルステート。
		ID3D11RasterizerState* rasterrizerState = nullptr;		//!<現在のラスタライザステート。
		ID3D11BlendState* blendState = nullptr;			//!<現在のブレンドステート。

	};

	SRenderState m_currentRenderState;	//現在のレンダリングステート。
	std::stack< SRenderState> m_renderStateStack;	//レンダリングステートのスタック。

	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。

	const int				m_2dSpaceScreenWidth = 1280;				//!<2D空間のスクリーンの幅。2Dはこの座標系を前提に表示されていれば、解像度が変わっても大丈夫。
	const int				m_2dSpaceScreenHeight = 720;				//!<2D空間のスクリーンの高さ。2Dはこの座標系を前提に表示されていれば、解像度が変わっても大丈夫。
	//Sprite
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン