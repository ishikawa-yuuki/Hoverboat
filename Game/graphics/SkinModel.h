#pragma once

#include "Skeleton.h"

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/

	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);

	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}

	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix ,EnRenderMode renderMode);

	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}

	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}

	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};

	/// <summary>
/// シャドウレシーバーのフラグを設定する。
/// </summary>
/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
/// <remarks>
/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
/// シャドウキャスターによって生成された、シャドウマップを利用して
/// 自身に影を落とします。
/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}

	/// <summary>
	/// 法線マップの設定。
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}

	/// <summary>
	/// スペキュラマップを設定。
	/// </summary>
	/// <param name="srv"></param>
	void SetSpecularMap(ID3D11ShaderResourceView* srv)
	{
		m_specularMapSRV = srv;
	}
	/// <summary>
	/// モデル事のライトの設定
	/// </summary>
	void SetLight(int i,CVector4 color)
	{
		m_light.dirLight.color[i] = color;
	}
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	ディレクションライトの作成。
	*/
	void InitDirectionLight();

	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	int R(int n) {
		return(((n - 1) / 16) + 1) * 16;
	}
private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ライトビュー行列。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
		int isShadowReciever;	//todo シャドウレシーバーのフラグ。
		int isHasSpecularMap;	//スペキュラマップある？
		int isHasNormalMap;		//法線マップを保持している？
	};
	bool m_isShadowReciever = false;						//シャドウレシーバーのフラグ。
/*!
 * @brief ディレクションライト
 */
	static const int LIGHT = 4;
	struct SDirectionLight {
		CVector4 direction[LIGHT];    //ライトの方向。
		CVector4 color[LIGHT];        //ライトのカラー。
	};
/*!
 * @brief ライト用の定数バッファ
 */
	struct LightCb {
		SDirectionLight dirLight; //ディレクションライト
		CVector3		eyePos;				//カメラの視点。
		float		    specPow;            //スペキュラライトの絞り。
		CVector3        ambientLight;       //アンビエントライト
	};
	float m_specPow = 0.5f;
	CVector4 m_color = { 1.0f,1.0f,1.0f,0.5f };
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	ID3D11Buffer*       m_lightCb = nullptr;            //!<ライト用の定数バッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	LightCb				m_light;						//!<ライト構造体
	SVSConstantBuffer  m_vsCb;							//!<定数バッファ。
	ID3D11ShaderResourceView* m_specularMapSRV = nullptr;	//スペキュラマップのSRV
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//法線マップのSRV
};