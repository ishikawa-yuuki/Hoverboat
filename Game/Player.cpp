#include "stdafx.h"
#include "Player.h"
#include "GameData.h"
#include "CPSwitchG.h"
#include "WeekBackPass.h"
#include "CoursePass.h"
#include "PlayerPad.h"
#include "ComputerPad.h"

Player::Player()
{
	//データの取得、初期化
	m_gamedata = &GameData::GetInstance();
	Data();
	m_animClip[enAnimationClip_test].Load(L"Assets/animData/test.tka");
	m_animClip[enAnimationClip_test].SetLoopFlag(true);
	m_model.Init(m_name);
	m_animation.Init(m_model, m_animClip, enAnimationClip_num);
	m_animation.Play(0);
	
	
}
Player::~Player()
{
	
}
/// <summary>
/// デリートする前に呼ぶ
/// </summary>
void Player::Release()
{
	m_charaCon.RemoveRigidBoby();
	//エフェクトを破棄。
	if (m_sampleEffect != nullptr) {
		g_goMgr->GetEffectManeger()->StopEffect(m_playEffectHandle);
		m_sampleEffect->Release();
	}
}
/// <summary>
/// キャラのデータ、当たり判定
/// </summary>
void Player::Data()
{
	//バイナリデータからキャラ情報取得
	FILE* fp = fopen("Assets/Character_Data/CharacterData/data.ai", "rb");
	int charaNoKazu;
	int charaNum = 0;
	fread(&charaNoKazu, sizeof(int), 1, fp);
	m_playerData = new PlayerData[charaNoKazu];
	fread(m_playerData, sizeof(PlayerData) * charaNoKazu, 1, fp);
	fclose(fp);

	charaNum = m_gamedata->GetCharaNum(charaNoKazu);

	//パス名(.cmo)
	size_t convSize;
	//utf-8からワイド文字列に変換。
	mbstowcs_s(
		&convSize, 
		m_name, 
		256, 
		m_playerData[charaNum].name,
		255
	);
	//パス名(.dds)
	mbstowcs_s(
		&convSize,
		m_specName,
		256,
		m_playerData[charaNum].specpass,
		255
	);

    //ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/hover/TX_tile_square_05_NRM.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_normalMapSRV);

	//ファイル名を使って、テクスチャをロードして、ShaderResourceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), m_specName, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_specMapSRV);

	//法線マップ設定
	m_model.SetNormalMap(m_normalMapSRV);
	//スペキュラマップ設定
	m_model.SetSpecularMap(m_specMapSRV);
}
void Player::EffectFollowing()
{
	//エフェクト追従計算
	CQuaternion effectrot;
	CQuaternion rot;
	CVector3 pos;
	CVector3 po1 = { 0.0f,0.0f,50.0f };
	effectrot = m_rot;
	pos = m_position;
	pos.y += 20.0f;
	rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	effectrot.Multiply(rot);
	effectrot.Multiply(po1);
	pos += po1;
	CMatrix mTrans, mRot, mScale, mBase;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(effectrot);
	mScale.MakeScaling(CVector3::One());
	mBase.Mul(mScale, mRot);
	mBase.Mul(mBase, mTrans);
	g_goMgr->GetEffectManeger()->SetBaseMatrix(m_playEffectHandle, mBase);
}
void Player::CheckGhost()
{
	//ゴースト(当たり判定)接触判定
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		//リストから当たり判定を取得
		ghostObj = m_cpGhostList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//
				m_gamePad->HitGhost();
			}
			});
	}
}
void Player::ReStartPass()
{
	//リスタート用ゴースト(当たり判定)接触判定
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_reStartPassList.size(); j++) {
		if (!m_reStartOver[j]) {
			//リストから当たり判定を取得
			ghostObj = m_reStartPassList[j]->GetGhost();
			g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject)) {//== true
					m_reStartOver[j] = true;
					m_reStart = true;
					m_reStartPos = m_reStartPassList[j]->GetPosition();
					m_gamePad->HitReStartPos();
				}
				});
		}
	}
}
void Player::CheckPass()
{
	//周回用ゴースト(当たり判定)接触判定
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		ghostObj = m_weekbackPassList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//周回判定する場所
				if (j == 0)
					WeekBack();
				else {
					m_weekBackOver[j] = true;
				}
			}
			});
	}
}
void Player::WeekBack()
{
	//スタート地点にて精算
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		if (m_weekBackOver[j]) {
			m_passNum++;
		}
		m_weekBackOver[j] = false;
	}
	//すべて通過していたらカウント
	if (m_passNum == m_weekbackPassList.size() - 1)
	{
		m_passNum = 0;
		m_weekbackNum++;

		//リスタート情報リセット
		for (int j = 0; j < m_reStartPassList.size(); j++) {
			m_reStartOver[j] = false;
		}
	}
	


}
void Player::HitDead()
{
	//落下死用ゴースト(当たり判定)接触判定
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_deadZoneList.size(); j++) {
		//リストから当たり判定取得
		ghostObj = m_deadZoneList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				m_isDead = true;
			}
			});
	}
}
/// <summary>
/// キャラの動き
/// </summary>
void Player::Start()
{
	//キャラコンを初期化
	m_charaCon.Init(
		m_radius,	//半径
		m_height,	//高さ
		m_position	//初期位置
	);
	
	//サンプルのエフェクトをロードする。

	m_sampleEffect = Effekseer::Effect::Create(g_goMgr->GetEffectManeger(), (const EFK_CHAR*)L"Assets/effect/fire.efk");
	////エフェクトを再生する。
	m_playEffectHandle = g_goMgr->GetEffectManeger()->Play(m_sampleEffect, 0.0f, 0.0f, 0.0f);	
	//////////
	//ListではなくPlayerクラスに通過判定のみ隔離（他プレイヤーと共通化してしまうため）
	//////////
	m_weekBackOver.resize(m_weekbackPassList.size());
	m_reStartOver.resize(m_reStartPassList.size());

	m_first = true;
}
void Player::Rotation()
{
	m_gamePad->Rotation();
	CVector3 stick;
	stick.x = m_gamePad->GetLstickXF();
	m_rot = m_gamePad->GetRotation();
	//摩擦
	if (fabsf(stick.x) >= 0.8f&&m_charaCon.IsOnGround())
	{
		m_friction *= m_playerData[m_charaNum].friction;
	}
	else {
		m_friction *= m_frictionAdd;
		if (m_friction >= m_frictionOver) {
			m_friction = m_frictionOver;
		}
	}

}
void Player::Move()
{
	m_gamePad->Move();
	if (m_gamePad->IsPressAccel())
	{
		m_accel = m_gamePad->GetDirection() * m_movePower;
	}
	else {
		m_accel = CVector3::Zero();
	}
	m_moveSpeed += m_accel * m_playerData[m_charaNum].accel;	//奥方向への移動速度を代入。
	m_moveSpeed *= m_friction;//摩擦を乗算
}
void Player::Jump()
{
	//入力時間分飛ぶ
	if (m_gamePad->IsPressJump() && m_jumpPower <= 0.2f&&!m_isJump)
	{
		m_jumpPower += GameTime().GetFrameDeltaTime();
		m_jump.y = m_Addjump * m_jumpPower;
	}
	else {
		if (m_charaCon.IsJump())
		{
			m_isJump = true;
		}
		m_jump = CVector3::Zero();
		if (m_charaCon.IsOnGround()) {
			m_moveSpeed.y = 0.0f;
			m_jumpPower = 0.0f;
			m_isJump = false;
		}
		else
		{
			m_moveSpeed.y -= m_gravity;
		}
	}
	

	m_moveSpeed += m_jump * 5.0f;
}

void Player::Update()
{
	//一度だけ実行
	if (!m_first) {
		Start();
	}
	
	if (m_weekbackNum == 3 &&!m_one)
	{
	
		//ゴール
		m_goal = true;
		m_one  = true;
	}
	else {
		m_goal = false;
	}
	
	

	if (!m_gamedata->GetGoal()) {


		if (m_gamePad != nullptr)
		{
			//レース開始準備
			if (m_gamedata->GetPose())
			{
				{
					EffectFollowing();
				}
				m_rot = m_gamePad->GetRotation();
				m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
				m_animation.Update(GameTime().GetFrameDeltaTime());
				m_charaCon.SetPosition(m_position);
				g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
				m_reStartPos = m_position;
				m_gamePad->HitReStartPos();
				return;
			}
			if (m_isDead)
			{
				//復活中
				if (!m_isTime) {
					m_gamePad->isDead();
					m_position = m_reStartPos;
					m_rot = m_gamePad->GetRotation();
					m_moveSpeed = CVector3::Zero();
					m_isTime = true;
				}
				else {
					m_cooltime += GameTime().GetFrameDeltaTime();
				}

				if (m_cooltime >= 0.5f)
				{
					m_isDead = false;
					m_isTime = false;
					m_cooltime = 0.0f;
				}
				//モデル更新
				m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
				//アニメーション更新
				m_animation.Update(GameTime().GetFrameDeltaTime());
				//キャラコン更新
				m_charaCon.SetPosition(m_position);
				//シャドウキャスターに登録。
				g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
				
				return;
			}
			//回転
			Rotation();
			//ジャンプ
			Jump();
			//移動
			Move();
			//当たり判定
			CheckGhost();
			//周回用当たり判定
			CheckPass();
			//リスタート用当たり判定
			ReStartPass();
			//落下死用当たり判定
			HitDead();
			
			
			m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
			
		}

		{
			//エフェクト追従
			EffectFollowing();
		}
		//ワールド行列の更新。
		m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
		m_animation.Update(GameTime().GetFrameDeltaTime());
		m_charaCon.SetPosition(m_position);
		g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
	}
	
}
void Player::Render()
{
	//シルエット描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Silhouette
	);
	//通常描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}