#pragma once
#include <vector>
#include "IGameObject.h"
#include "ShadowMap.h"
#include "RenderTarget.h"
#include "Sprite.h"
#include "SoundEngine.h"
#include "PostEffect.h"
class GameObjectManager
{
public:
	bool Start();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// ゲームオブジェクトを追加。
	/// </summary>
	template <class T>
	T* NewGameObject()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// ゲームオブジェクトを削除。
	/// </summary>
	/// <param name="go">
	/// ゲームオブジェクト名
	/// </param>
	void DeleteGameObject(IGameObject* go)
	{
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++)
		{
			if ((*it == go))
			{
				go->RequestDelete();
				return;
			}
		}
	}
	/// <summary>
	/// メインレンダリングターゲットを取得。
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	void SetShadowPos()
	{
		m_shadowMapPos = m_shadowMapTarget + m_shadow;
	}
	void SetShadowTarget(CVector3 const& pos)
	{
		m_shadowMapTarget = pos;
	}
	/// <summary>
/// シャドウマップを取得。
/// </summary>
/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
	Effekseer::Manager* GetEffectManeger()
	{
		return m_effekseerManager;
	}
	/// <summary>
	/// プリレンダリング。
	/// </summary>
	void PreRender();
	/// <summary>
	/// フォワードレンダリング(通常の描画だと考えてOK)
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// ポストレンダリング
	/// </summary>
	void PostRender();
	/// <summary>
   /// Effekseerの初期化。
   /// </summary>
	void InitEffekseer();
	
private:
	//Effekseerマネージャ管理。
	Effekseer::Manager* m_effekseerManager				= nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer	= nullptr;
	PostEffect m_postEffect;						//ポストエフェクト。
	CSoundEngine m_soundEngine;						//サウンドエンジン。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	RenderTarget m_mainRenderTarget;			    //メインレンダリングターゲット
	ShadowMap m_shadowMap;							//シャドウマップ。
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	std::vector< IGameObject* > m_goList;		//ゲームオブジェクトのリスト。
	CVector3 m_shadowMapPos = { 800.0f,800.0f,800.0f };
	CVector3 m_shadow =  {800.0f,800.0f,800.0f} ;
	CVector3 m_shadowMapTarget = {0.0f,0.0f,0.0f};
	bool m_first = false;
};
//外部からアクセスするので、extern宣言も必要。
extern GameObjectManager* g_goMgr;
