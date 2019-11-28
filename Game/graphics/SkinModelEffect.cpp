#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"
#include "ShadowMap.h"
#include "GameObjectManager.h"
void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;                    //Z�e�X�g�L��
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;//Z�o�b�t�@��Z�l��`�����܂Ȃ�
	desc.DepthFunc = D3D11_COMPARISON_GREATER;//Z�l���傫����΃t���[���o�b�t�@�ɕ`������

	pd3d->CreateDepthStencilState(&desc, &m_depthState);
}
void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	
	
	switch (m_renderMode) {
	case enRenderMode_Normal: {
		//�ʏ�`��
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		//todo �V�F�[�_�[���\�[�X�r���[����C�ɐݒ肷��B
		ID3D11ShaderResourceView* srvArray[] = {
			m_albedoTexture,							//�A���x�h�e�N�X�`���B
			//g_goMgr->GetShadowMap()->GetShadowMapSRV()	//�V���h�E�}�b�v�B
		};
		deviceContext->PSSetShaderResources(0, 1, srvArray);
		srvArray[0] = g_goMgr->GetShadowMap()->GetShadowMapSRV();
		deviceContext->PSSetShaderResources(2, 1, srvArray);
	}break;
	case enRenderMode_Silhouette:
		//�V���G�b�g�`��
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pSSilhouette->GetBody(), NULL, 0);
	    //�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
		deviceContext->OMSetDepthStencilState(m_depthState, 0);
		break;
	case enRenderMode_CreateShadowMap:
		//�V���h�[
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}
