#include "stdafx.h"
#include "GameObjectManager.h"
#include "ShadowMap.h"
GameObjectManager* g_goMgr = nullptr;

void GameObjectManager::Update()
{
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	for (auto go : m_goList)
	{
		go->Update();
	}
	//���艟����
	//�V���h�E�}�b�v���X�V�B
	m_shadowMap.UpdateFromLightTarget(
		{ 800.0f, 800.0f, 800.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	///////////////////////////////////////////////
	//�V���h�E�}�b�v�Ƀ����_�����O
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	////�V���h�E�}�b�v�Ƀ����_�����O
	m_shadowMap.RenderToShadowMap();

	//���ɖ߂��B
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
	/// 
	/// ���艟����
	/// 
	for (auto go : m_goList) {
		go->Render();
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
