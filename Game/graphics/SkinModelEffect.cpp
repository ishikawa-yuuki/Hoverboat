#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

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
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	
	switch (m_renderMode) {
	case 0:
		//通常描画
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);

		break;
	case 1:
		//シルエット描画
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pSSilhouette->GetBody(), NULL, 0);
	    //デプスステンシルステートを切り替える。
		deviceContext->OMSetDepthStencilState(m_depthState, 0);
		break;
	}
}
