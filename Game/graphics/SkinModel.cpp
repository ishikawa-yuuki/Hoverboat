#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"
#include "ShadowMap.h"
#include "GameObjectManager.h"
SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
}

void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

    InitDirectionLight();

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
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
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
    //続いてライトの定数バッファ作成
	bufferDesc.ByteWidth =R( sizeof(LightCb));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
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
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//定数バッファの内容を更新。
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

	//スペキュラマップを使用するかどうかのフラグを送る。
	if (m_specularMapSRV != nullptr) {
		m_vsCb.isHasSpecularMap = true;
	}
	else {
		m_vsCb.isHasSpecularMap = false;
	}

	//todo 法線マップを使用するかどうかのフラグを送る。
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
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->VSSetConstantBuffers(1, 1, &m_lightCb);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();
	//マテリアルにクエリを行う。
	m_modelDx->UpdateEffects([&](DirectX::IEffect * material) {
		auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
	});

	if (m_specularMapSRV != nullptr) {
		//スペキュラマップが設定されていたらレジスタt3に設定する。
		d3dDeviceContext->PSSetShaderResources(3, 1, &m_specularMapSRV);
	}
	if (m_normalMapSRV != nullptr) {
		//法線マップが設定されていたらをレジスタt4に設定する。
		d3dDeviceContext->PSSetShaderResources(4, 1, &m_normalMapSRV);
	}
	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}