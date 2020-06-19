#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"
#include "ShadowMap.h"
#include "GameObjectManager.h"
SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//�萔�o�b�t�@������B
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//�T���v���X�e�[�g������B
		m_samplerState->Release();
	}
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
}

void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	InitSkeleton(filePath);

	//�萔�o�b�t�@�̍쐬�B
	InitConstantBuffer();

	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

    InitDirectionLight();

	//SkinModelDataManager���g�p����CMO�t�@�C���̃��[�h�B
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	//cmo�t�@�C���̊g���q��tks�ɕύX����B
	std::wstring skeletonFilePath = filePath;
	//�����񂩂�.cmo�t�@�C���n�܂�ꏊ�������B
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmo�t�@�C����.tks�ɒu��������B
	skeletonFilePath.replace(pos, 4, L".tks");
	//tks�t�@�C�������[�h����B
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//�X�P���g�����ǂݍ��݂Ɏ��s�����B
		//�A�j���[�V�������Ȃ����f���́A�X�P���g�����s�v�Ȃ̂�
		//�ǂݍ��݂Ɏ��s���邱�Ƃ͂���̂ŁA���O�o�͂����ɂ��Ă����B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tks�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitDirectionLight()
{
	m_light.dirLight.direction[0] = {  1.0f,-0.5f, 0.0f,1.0f };
	m_light.dirLight.direction[1] = { -1.0f,-0.5f, 0.0f,1.0f };
	m_light.dirLight.direction[2] = {  0.0f, 0.0f,-1.0f,1.0f };
	m_light.dirLight.direction[3] = {  0.0f, 0.0f, 1.0f,1.0f };
	for (int i = 0; i < LIGHT; i++) {
		m_light.dirLight.color[i] = { 1.0f,1.0f,1.0f,1.0f };
	}
	m_light.specPow = 10.0f;
}
void SkinModel::InitConstantBuffer()
{
	//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
	int bufferSize = sizeof(SVSConstantBuffer);
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	//�쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
    //�����ă��C�g�̒萔�o�b�t�@�쐬
	bufferDesc.ByteWidth =R( sizeof(LightCb));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

}
void SkinModel::InitSamplerState()
{
	//�e�N�X�`���̃T���v�����O���@���w�肷�邽�߂̃T���v���X�e�[�g���쐬�B
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//���s�ړ��s����쐬����B
	transMatrix.MakeTranslation( position );
	//��]�s����쐬����B
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//�g��s����쐬����B
	scaleMatrix.MakeScaling(scale);
	//���[���h�s����쐬����B
	//�g��~��]�~���s�ړ��̏��Ԃŏ�Z����悤�ɁI
	//���Ԃ��ԈႦ���猋�ʂ��ς���B
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//�X�P���g���̍X�V�B
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�萔�o�b�t�@�̓��e���X�V�B
	m_vsCb.mWorld = m_worldMatrix;
	m_vsCb.mProj = projMatrix;
	m_vsCb.mView = viewMatrix;
	m_vsCb.mLightProj = g_goMgr->GetShadowMap()->GetLightProjMatrix();
	m_vsCb.mLightView = g_goMgr->GetShadowMap()->GetLighViewMatrix();

	if (m_isShadowReciever == true) {
		m_vsCb.isShadowReciever = 1;
	}
	else {
		m_vsCb.isShadowReciever = 0;
	}

	//�X�y�L�����}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_specularMapSRV != nullptr) {
		m_vsCb.isHasSpecularMap = true;
	}
	else {
		m_vsCb.isHasSpecularMap = false;
	}

	//todo �@���}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_normalMapSRV != nullptr) {
		m_vsCb.isHasNormalMap = true;
	}
	else {
		m_vsCb.isHasNormalMap = false;
	}
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &m_vsCb, 0, 0);
	m_light.eyePos = g_camera3D.GetPosition();
	m_light.ambientLight = CVector3{ 0.4f,0.4f,0.4f };
	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);
	//�萔�o�b�t�@��GPU�ɓ]���B
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->VSSetConstantBuffers(1, 1, &m_lightCb);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	//�T���v���X�e�[�g��ݒ�B
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//�{�[���s���GPU�ɓ]���B
	m_skeleton.SendBoneMatrixArrayToGPU();
	//�}�e���A���ɃN�G�����s���B
	m_modelDx->UpdateEffects([&](DirectX::IEffect * material) {
		auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
	});

	if (m_specularMapSRV != nullptr) {
		//�X�y�L�����}�b�v���ݒ肳��Ă����烌�W�X�^t3�ɐݒ肷��B
		d3dDeviceContext->PSSetShaderResources(3, 1, &m_specularMapSRV);
	}
	if (m_normalMapSRV != nullptr) {
		//�@���}�b�v���ݒ肳��Ă���������W�X�^t4�ɐݒ肷��B
		d3dDeviceContext->PSSetShaderResources(4, 1, &m_normalMapSRV);
	}
	//�`��B
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}