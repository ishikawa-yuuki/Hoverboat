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
	//�f�[�^�̎擾�A������
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
/// �f���[�g����O�ɌĂ�
/// </summary>
void Player::Release()
{
	m_charaCon.RemoveRigidBoby();
	//�G�t�F�N�g��j���B
	if (m_sampleEffect != nullptr) {
		g_goMgr->GetEffectManeger()->StopEffect(m_playEffectHandle);
		m_sampleEffect->Release();
	}
}
/// <summary>
/// �L�����̃f�[�^�A�����蔻��
/// </summary>
void Player::Data()
{
	//�o�C�i���f�[�^����L�������擾
	FILE* fp = fopen("Assets/Character_Data/CharacterData/data.ai", "rb");
	int charaNoKazu;
	int charaNum = 0;
	fread(&charaNoKazu, sizeof(int), 1, fp);
	m_playerData = new PlayerData[charaNoKazu];
	fread(m_playerData, sizeof(PlayerData) * charaNoKazu, 1, fp);
	fclose(fp);

	charaNum = m_gamedata->GetCharaNum(charaNoKazu);

	//�p�X��(.cmo)
	size_t convSize;
	//utf-8���烏�C�h������ɕϊ��B
	mbstowcs_s(
		&convSize, 
		m_name, 
		256, 
		m_playerData[charaNum].name,
		255
	);
	//�p�X��(.dds)
	mbstowcs_s(
		&convSize,
		m_specName,
		256,
		m_playerData[charaNum].specpass,
		255
	);

    //�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResrouceView���쐬����B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/hover/TX_tile_square_05_NRM.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_normalMapSRV);

	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResourceView���쐬����B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), m_specName, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_specMapSRV);

	//�@���}�b�v�ݒ�
	m_model.SetNormalMap(m_normalMapSRV);
	//�X�y�L�����}�b�v�ݒ�
	m_model.SetSpecularMap(m_specMapSRV);
}
void Player::EffectFollowing()
{
	//�G�t�F�N�g�Ǐ]�v�Z
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
	//�S�[�X�g(�����蔻��)�ڐG����
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		//���X�g���瓖���蔻����擾
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
	//���X�^�[�g�p�S�[�X�g(�����蔻��)�ڐG����
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_reStartPassList.size(); j++) {
		if (!m_reStartOver[j]) {
			//���X�g���瓖���蔻����擾
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
	//����p�S�[�X�g(�����蔻��)�ڐG����
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		ghostObj = m_weekbackPassList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//���񔻒肷��ꏊ
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
	//�X�^�[�g�n�_�ɂĐ��Z
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		if (m_weekBackOver[j]) {
			m_passNum++;
		}
		m_weekBackOver[j] = false;
	}
	//���ׂĒʉ߂��Ă�����J�E���g
	if (m_passNum == m_weekbackPassList.size() - 1)
	{
		m_passNum = 0;
		m_weekbackNum++;

		//���X�^�[�g��񃊃Z�b�g
		for (int j = 0; j < m_reStartPassList.size(); j++) {
			m_reStartOver[j] = false;
		}
	}
	


}
void Player::HitDead()
{
	//�������p�S�[�X�g(�����蔻��)�ڐG����
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_deadZoneList.size(); j++) {
		//���X�g���瓖���蔻��擾
		ghostObj = m_deadZoneList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				m_isDead = true;
			}
			});
	}
}
/// <summary>
/// �L�����̓���
/// </summary>
void Player::Start()
{
	//�L�����R����������
	m_charaCon.Init(
		m_radius,	//���a
		m_height,	//����
		m_position	//�����ʒu
	);
	
	//�T���v���̃G�t�F�N�g�����[�h����B

	m_sampleEffect = Effekseer::Effect::Create(g_goMgr->GetEffectManeger(), (const EFK_CHAR*)L"Assets/effect/fire.efk");
	////�G�t�F�N�g���Đ�����B
	m_playEffectHandle = g_goMgr->GetEffectManeger()->Play(m_sampleEffect, 0.0f, 0.0f, 0.0f);	
	//////////
	//List�ł͂Ȃ�Player�N���X�ɒʉߔ���̂݊u���i���v���C���[�Ƌ��ʉ����Ă��܂����߁j
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
	//���C
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
	m_moveSpeed += m_accel * m_playerData[m_charaNum].accel;	//�������ւ̈ړ����x�����B
	m_moveSpeed *= m_friction;//���C����Z
}
void Player::Jump()
{
	//���͎��ԕ����
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
	//��x�������s
	if (!m_first) {
		Start();
	}
	
	if (m_weekbackNum == 3 &&!m_one)
	{
	
		//�S�[��
		m_goal = true;
		m_one  = true;
	}
	else {
		m_goal = false;
	}
	
	

	if (!m_gamedata->GetGoal()) {


		if (m_gamePad != nullptr)
		{
			//���[�X�J�n����
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
				//������
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
				//���f���X�V
				m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
				//�A�j���[�V�����X�V
				m_animation.Update(GameTime().GetFrameDeltaTime());
				//�L�����R���X�V
				m_charaCon.SetPosition(m_position);
				//�V���h�E�L���X�^�[�ɓo�^�B
				g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
				
				return;
			}
			//��]
			Rotation();
			//�W�����v
			Jump();
			//�ړ�
			Move();
			//�����蔻��
			CheckGhost();
			//����p�����蔻��
			CheckPass();
			//���X�^�[�g�p�����蔻��
			ReStartPass();
			//�������p�����蔻��
			HitDead();
			
			
			m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
			
		}

		{
			//�G�t�F�N�g�Ǐ]
			EffectFollowing();
		}
		//���[���h�s��̍X�V�B
		m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
		m_animation.Update(GameTime().GetFrameDeltaTime());
		m_charaCon.SetPosition(m_position);
		g_goMgr->GetShadowMap()->RegistShadowCaster(&m_model);
	}
	
}
void Player::Render()
{
	//�V���G�b�g�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Silhouette
	);
	//�ʏ�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal
	);
}