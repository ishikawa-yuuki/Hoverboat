#pragma once
#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
#include "GameObjectManager.h"
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
	void WeekBack();
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
private:
	enum HumanAnimationClip {
		enAnimationClip_test,
		enAnimationClip_num
	};
	AnimationClip m_animClip[enAnimationClip_num];
	Animation m_animation;
	PlayerData m_playerData;//�L�������̃p�����[�^
	SkinModel m_model;	//�X�L�����f���B
	CharacterController m_charaCon;
	std::vector<CoursePass*> m_courcePassList;
	std::vector<CPSwitchG*> m_cpGhostList;
	std::vector<WeekBackPass*> m_weekbackPassList;
	GamePad* m_gamePad	 = nullptr;			
	CVector3 m_position  = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_accel	 = CVector3::Zero();	//�����x
	CVector3 m_jump		 = CVector3::Zero();     //�W�����v�̉����x
	CQuaternion m_rot	 = CQuaternion::Identity();
	float m_friction	 = 0.98f;   //���C�x
	float m_movePower	 = 100.0f;// �ړ����x
	bool m_first		 = false;

};


