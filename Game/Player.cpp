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
	m_animClip[enAnimationClip_test].Load(L"Assets/animData/test.tka");
	m_animClip[enAnimationClip_test].SetLoopFlag(true);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/hover/Hope.cmo");
	/*m_model.PlayAnimation(enAnimationClip_test, 0.2);*/
	m_animation.Init(m_model, m_animClip, enAnimationClip_num);
	m_animation.Play(0,0.4f);
}


Player::~Player()
{
	//�G�t�F�N�g��j���B(�����܂���j
	if (m_sampleEffect != nullptr) {
		m_sampleEffect->Release();
	}
}
/// <summary>
/// �L�����̃f�[�^�A�����蔻��
/// </summary>
void Player::Data()
{
	FILE* fp = fopen("Assets/Character_Data/CharacterData/data.ai", "rb");
	int charaNoKazu;
	fread(&charaNoKazu, sizeof(int), 1, fp);
	m_playerData = new PlayerData[charaNoKazu];
	fread(m_playerData, sizeof(PlayerData) * charaNoKazu, 1, fp);
	fclose(fp);
}
void Player::CheckGhost()
{
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_cpGhostList.size(); j++) {
		ghostObj = m_cpGhostList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//
				m_gamePad->HitGhost();
			}
			});
	}
}
void Player::CheckCourcePass()
{
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_courcePassList.size(); j++) {
		ghostObj = m_courcePassList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//
				m_gamePad->HitCourcePass();
			}
			else {
				m_gamePad->NotHitPass();
			}
			});
	}
}
void Player::CheckPass()
{
	PhysicsGhostObject* ghostObj = nullptr;
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		ghostObj = m_weekbackPassList[j]->GetGhost();
		g_physics.ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
			if (ghostObj->IsSelf(contactObject)) {//== true
				//���񔻒肷��ꏊ
				if (j == 0)
					WeekBack();
				else {
					m_over[j] = true;
				}
			}
			});
	}
}
void Player::WeekBack()
{
	//�X�^�[�g�n�_�ɂĐ��Z
	for (int j = 0; j < m_weekbackPassList.size(); j++) {
		if (m_over[j]) {
			m_passNum++;
		}
		m_over[j] = false;
	}
	if (m_passNum == m_weekbackPassList.size() - 1)
	{
		m_passNum = 0;
		m_weekbackNum++;
	}

}
/// <summary>
/// �L�����̓���
/// </summary>
bool Player::Start()
{
	m_gamedata = &GameData::GetInstance();
	Data();
	m_charaCon.Init(
		30.0f,
		20.0f,
		m_position
	);
	//m_rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	//�T���v���̃G�t�F�N�g�����[�h����B

	m_sampleEffect = Effekseer::Effect::Create(g_goMgr->GetEffectManeger(), (const EFK_CHAR*)L"Assets/effect/fire.efk");
	////�G�t�F�N�g���Đ�����B
	m_playEffectHandle = g_goMgr->GetEffectManeger()->Play(m_sampleEffect, 0.0f, 0.0f, 0.0f);

	//////////
	//List�ł͂Ȃ�Player�N���X�ɒʉߔ���̂݊u���i���v���C���[�Ƌ��ʉ����Ă��܂����߁j
	//////////
	m_over.resize(m_weekbackPassList.size());

	m_first = true;
	return true;
}
void Player::Rotation()
{
	m_gamePad->Rotation();
	CVector3 stick;
	stick.x = m_gamePad->GetLstickXF();
	m_rot = m_gamePad->GetRotation();
	if (fabsf(stick.x) >= 0.8f)
	{
		m_friction *= m_playerData[m_charaNum].friction;
	}
	else {
		m_friction *= 1.01f;
		if (m_friction >= 0.98f) {
			m_friction = 0.98f;
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
	m_moveSpeed *= m_friction;//���C
}
void Player::Jump()
{

	if (m_gamePad->IsPressJump() )
	{
		m_jump.y = 10.0f;
	}
	else {
		m_jump = CVector3::Zero();
		if (m_charaCon.IsOnGround()) {
			m_moveSpeed.y = 0.0f;
		}
		else
		{
			m_moveSpeed.y -= 100.0f;
		}
	}
	m_moveSpeed += m_jump * 5.0f;
}

void Player::Update()
{
	if (m_weekbackNum == 3)
	{
	
		//�S�[��
		m_gamedata->SetGoal();
	}
	
	if (!m_first) {
		Start();
	}

	if (!m_gamedata->GetGoal()) {


		{
			CMatrix mTrans, mRot, mScale, mBase;
			mTrans.MakeTranslation(m_position);
			mRot.MakeRotationFromQuaternion(CQuaternion::Identity());
			mScale.MakeScaling(CVector3::One());
			mBase.Mul(mScale, mRot);
			mBase.Mul(mBase, mTrans);
			g_goMgr->GetEffectManeger()->SetBaseMatrix(m_playEffectHandle, mBase);
		}
		if (m_gamePad != nullptr)
		{
			Rotation();
			Jump();
			Move();
			CheckGhost();
			CheckPass();
			//CheckCourcePass();
			m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
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
	//�e�X�g(���C�g���񂷁j
	//m_model.Update();
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