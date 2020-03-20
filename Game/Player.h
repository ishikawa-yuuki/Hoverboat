#pragma once
#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
#include "GameObjectManager.h"
class GameData;
class GamePad;
class CPSwitchG;
class CoursePass;
class WeekBackPass;
struct PlayerData {
	float accel;//�����x
	float friction;//���C�x
	float sutearing;
};
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render();
	void Rotation();
	void Release();
	void Move();
	void Jump();
	/// <summary>
	/// �S�[�X�g���菈��
	/// </summary>
	void CheckGhost();
	/// <summary>
	/// ����p�S�[�X�g����
	/// </summary>
	void CheckPass();

	void CheckCourcePass();
	void ReStartPass();
	void WeekBack();
	void HitDead();
	void Data();
	void SetChara(const int& num)
	{
		m_charaNum = num;
	}
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}

	/*!
	 *@brief	Player��Position���擾�B
	 */
	const CVector3& GetPosition()const
	{
		return m_position;
	}

	/*!
	 *@brief	Player��CQuaternion���擾�B
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
	bool GetDead()
	{
		return m_isDead;
	}
	bool GetReStart()
	{
		return m_reStart;
	}
	int GetWeekBack()
	{
		return m_weekbackNum;
	}
	void SetReStart() {
		m_reStart = false;
	}
	/// <summary>
	/// �S�[������
	/// </summary>
	/// <returns></returns>
	bool GetPlayerGoal()
	{
		return m_goal;
	}
	void SetPad(GamePad* gamePad)
	{
		m_gamePad = gamePad;
	}
	const std::vector<CPSwitchG*>& SetGhostObjectList(const std::vector<CPSwitchG*>& List)
	{
		m_cpGhostList = List;
		return m_cpGhostList;
	}
	const std::vector<CoursePass*>& SetPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_courcePassList = List;
		return m_courcePassList;
	}
	const std::vector<CoursePass*>& SetReStartPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_reStartPassList = List;
		return m_reStartPassList;
	}
	const std::vector<CoursePass*>& SetDeadZonePassObjectList(const std::vector<CoursePass*>& List)
	{
		m_deadZoneList = List;
		return m_deadZoneList;
	}
	const std::vector<WeekBackPass*>& SetWeekPassObjectList(const std::vector<WeekBackPass*>& List)
	{
		m_weekbackPassList = List;
		return m_weekbackPassList;
	}
private:
	enum HumanAnimationClip {
		enAnimationClip_test,
		enAnimationClip_num
	};
	AnimationClip m_animClip[enAnimationClip_num];
	Animation m_animation;
	SkinModel m_model;	//�X�L�����f���B
	CharacterController m_charaCon;
	std::vector<CoursePass*> m_courcePassList;
	std::vector<CoursePass*> m_reStartPassList;     //���������㕜������|�W�V����
	std::vector<CPSwitchG*> m_cpGhostList;
	std::vector<WeekBackPass*> m_weekbackPassList;
	std::vector<CoursePass*> m_deadZoneList;
	//Effekseer::Effect* m_sampleEffect = nullptr;
	//Effekseer::Handle m_playEffectHandle = -1;
	PlayerData* m_playerData		  = nullptr;//�L�������̃p�����[�^
	GamePad* m_gamePad	              = nullptr;			
	GameData* m_gamedata			  = nullptr;
	CVector3 m_position  = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_accel	 = CVector3::Zero();	//�����x
	CVector3 m_jump		 = CVector3::Zero();     //�W�����v�̉����x
	CVector3 m_reStartPos = CVector3::Zero();
	CQuaternion m_reStartRot = CQuaternion::Identity();
	CQuaternion m_rot	 = CQuaternion::Identity();
	CQuaternion m_effectRot = {0.0f,0.0f,90.0f,1.0f};

	float m_friction	 = 0.98f;   //���C�x
	float m_movePower	 = 100.0f;	// �ړ����x
	float m_jumpPower	 = 0.0f;
	float m_cooltime = 0.0f;
	int m_passNum		 = 0;
	int m_weekbackNum	 = 0;
	int m_charaNum		 = 0;
	bool m_first		 = false;
	bool m_goal			 = false;
	bool m_one			 = false;
	bool m_isDead = false;
	bool m_reStart = false;
	bool m_isJump = false;
	bool m_isTime = false;
	std::vector<bool> m_weekBackOver;
	std::vector<bool> m_reStartOver;
};


