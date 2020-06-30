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
	//Effekseer���������B
	InitEffekseer();

	m_first = true;
	return true;
}
void GameObjectManager::InitEffekseer()
{
	//�����_���[���������B
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());

}

void GameObjectManager::PreRender() {
	

	////�V���h�E�}�b�v�Ƀ����_�����O
	m_shadowMap.RenderToShadowMap();

}
void GameObjectManager::ForwordRender() {
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	g_graphicsEngine->ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	
}
void GameObjectManager::PostRender() {

	Fade().PostRender();
	//�|�X�g�G�t�F�N�g�̕`��B
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
	
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̃|�X�g�����_�[�ĂԁB
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
		//Effekseer�J�����s���ݒ�B
	//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseer���X�V�B
		m_effekseerManager->Update();

//�V���h�E�}�b�v���X�V�B
		m_shadowMap.UpdateFromLightTarget(
			m_shadowMapPos,
			m_shadowMapTarget
		);

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
		for (auto go : m_goList)
		{
			go->Update();
			Fade().Update();
		}
		//�|�X�g�G�t�F�N�g�̍X�V�B
		m_postEffect.Update();

//�`��
		//�t���[���o�b�t�@�̂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);
		//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

	
	
//�v�������_�����O�B
		PreRender();
/// �t�H���[�h�����_�����O(�ʏ�̕`�悾�ƍl����OK)
		ForwordRender();
//�ʏ�`��
		for (auto go : m_goList) {
			go->Render();
		}
		
		//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
		
// �|�X�g�����_�����O
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
