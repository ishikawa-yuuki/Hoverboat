/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);		//アルベドテクスチャ
Texture2D<float4> g_shadowMap   : register(t2);		//シャドウマップ。
Texture2D<float4> g_specularMap : register(t3);		//スペキュラマップ。
Texture2D<float4> g_normalMap   : register(t4);		//法線マップ。
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasSpecularMap;	//スペキュラマップある？
	int isHasNormalMap;		//法線マップある？
};
/*!
*@brief ディレクションライト
*/
static const int LIGHT = 4;
struct SDirectionLight {
	float3 direction[LIGHT];
	float4 color[LIGHT];
};
/*!
 * @brief ライト用の定数バッファ
 */
cbuffer LightCb : register(b1) {
	SDirectionLight dirLight;
	float3 eyePos;				//カメラの視点。
	float  specPow;            //スペキュラライトの絞り。
	float3 ambientLight;//アンビエントライト
};
/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}
/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////

/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};
/// <summary>
/// シャドウマップ用のピクセルシェーダーの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float4 worldPos		: TEXCOORD1;	//ワールド座標
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/// <summary>
/// ラインバート拡散反射を計算する。
/// </summary>
float3 CalcDiffuseLight(float3 normal)
{
	float3 lig = 0.0f;
	for (int i = 0; i < LIGHT; i++) {
		//ランバート拡散反射。(少し暗く)
		lig += max(0.0f, dot(normal * -0.7f, dirLight.direction[i])) * dirLight.color[i];
	}
	return lig;
}
/// <summary>
/// スペキュラライトを計算する。
/// </summary>
float3 CalcSpecularLight(float3 normal, float3 worldPos, float2 uv)
{
	float3 lig = 0.0f;
	
	for (int i = 0; i < LIGHT; i++) {
		
		//ライトを当てる面から視点に伸びるベクトルtoEyeDirを求める。
		//	 視点の座標は定数バッファで渡されている。LightCbを参照するように。
		float3 toEyeDir = normalize(eyePos - worldPos);
		// toEyeDirの反射ベクトルを求める。
		float3 reflectEyeDir = -toEyeDir + 2 * dot(normal, toEyeDir) * normal;
		// 反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算する。
		float t = max(0.0f, dot(-dirLight.direction[i], reflectEyeDir));
		// pow関数を使って、スペキュラを絞る。絞りの強さは定数バッファで渡されている。
		//	 LightCbを参照するように。
		float specPower = 1.0f;
		if (isHasSpecularMap) {
			//スペキュラマップがある。
			specPower = g_specularMap.Sample(g_sampler, uv).r;
		}
		else {
			specPower = 0.08f;
		}
		float3 specLig = pow(t, specPow) * dirLight.color[i] * specPower * 7.0f;
		// スペキュラ反射が求まったら、ligに加算する。
		//鏡面反射を反射光に加算する。
		lig += specLig;
	}
	return lig;
}
/// <summary>
/// 法線を計算する。
/// </summary>
float3 CalcNormal(float3 normal, float3 tangent, float2 uv)
{
	float3 worldSpaceNormal;
	if (isHasNormalMap == 1) {
		//法線マップがある。
		//法線と接ベクトルの外積を計算して、従ベクトルを計算する。
		float3 biNormal = cross(normal, tangent);
		float3 tangentSpaceNormal = g_normalMap.Sample(g_sampler, uv);
		//0.0～1.0の範囲になっているタンジェントスペース法線を
		//-1.0～1.0の範囲に変換する。
		tangentSpaceNormal = (tangentSpaceNormal * 2.0f) - 1.0f;
		//法線をタンジェントスペースから、ワールドスペースに変換する。
		worldSpaceNormal = tangent * tangentSpaceNormal.x + biNormal * tangentSpaceNormal.y + normal * tangentSpaceNormal.z;
	}
	else {
		//ない。
		worldSpaceNormal = normal;
	}
	return worldSpaceNormal;
}
/// <summary>
/// デプスシャドウマップ法を使って、影を計算する。。
/// </summary>
//引数にinoutをつけると参照渡しになる。
void CalcShadow(inout float3 lig, float4 posInLvp)
{
	if (isShadowReciever == 1) {	//シャドウレシーバー。
		//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = posInLvp.xy / posInLvp.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

			///LVP空間での深度値を計算。
			float zInLVP = posInLvp.z / posInLvp.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV);

			if (zInLVP > zInShadowMap + 0.01f) {
				//影が落ちているので、光を弱くする
				lig *= 0.7f;
			}
		}
	}
}
/*!--------------------------------------------------------------------------------------
 * @brief	シャドウマップ生成用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	psInput.worldPos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, psInput.worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize( mul(mWorld, In.Normal));
	psInput.Tangent = normalize( mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
		/*psInput.worldPos = pos;*/
	}
	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, psInput.worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(g_sampler, In.TexCoord);

	//法線を計算する。
	float3 normal = CalcNormal(In.Normal, In.Tangent, In.TexCoord);
	
	float3 lig = 0.0f;

	//ディフューズライトを加算。
	lig += CalcDiffuseLight(normal);
	//スペキュラライトを加算。
	lig += CalcSpecularLight(normal, In.worldPos, In.TexCoord);

	lig += ambientLight;

	//デプスシャドウマップを使って影を落とす。。
	CalcShadow(lig, In.posInLVP);

	float4 finalColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}

