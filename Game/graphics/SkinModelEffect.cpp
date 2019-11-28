#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"
#include "ShadowMap.h"
#include "GameObjectManager.h"
void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;                    //Zテスト有効
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;//ZバッファにZ値を描きこまない
	desc.DepthFunc = D3D11_COMPARISON_GREATER;//Z値が大きければフレームバッファに描きこむ

	pd3d->CreateDepthStencilState(&desc, &m_depthState);
}
void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	
	
	switch (m_renderMode) {
	case enRenderMode_Normal: {
		//通常描画
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		//todo シェーダーリソースビューを一気に設定する。
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTexture,							//アルベドテクスチャ。
			//g_goMgr->GetShadowMap()->GetShadowMapSRV()	//シャドウマップ。
		};
		deviceContext->PSSetShaderResources(0, 1, srvArray);
		srvArray[0] = g_goMgr->GetShadowMap()->GetShadowMapSRV();
		deviceContext->PSSetShaderResources(2, 1, srvArray);
	}break;
	case enRenderMode_Silhouette:
		//シルエット描画
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pSSilhouette->GetBody(), NULL, 0);
	    //デプスステンシルステートを切り替える。
		deviceContext->OMSetDepthStencilState(m_depthState, 0);
		break;
	case enRenderMode_CreateShadowMap:
		//シャドー
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}
