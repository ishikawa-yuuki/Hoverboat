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
	float accel;//�����x       4byte
	float friction;//���C�x    4byte
	float sutearing;           //4byte
    char name[256];           //256byte
	char specpass[256];		 //256byte
};
class Player : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// Update�̒��O�ŌĂԊJ�n����
	/// </summary>
	void Start();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();

	void Release();

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �W�����v����
	/// </summary>
	void Jump();

	/// <summary>
	/// �S�[�X�g���菈��
	/// </summary>
	void CheckGhost();

	/// <summary>
	/// ����p�S�[�X�g����
	/// </summary>
	void CheckPass();

	/// <summary>
	/// ���X�^�[�g�n�_�ʉߔ���
	/// </summary>
	void ReStartPass();

	/// <summary>
	/// ����J�E���g������
	/// </summary>
	void WeekBack();

	/// <summary>
	/// ��������
	/// </summary>
	void HitDead();

	/// <summary>
	/// �L�����̃f�[�^�A�����蔻��
	/// </summary>
	void Data();

	/// <summary>
	/// �G�t�F�N�g�Ǐ]
	/// </summary>
	void EffectFollowing();

	void SetChara(const int& num)
	{
		m_charaNum = num;
	}

	/*!
	 *@breif   Player��Position��ݒ�B
	*/
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
	/*!
	 *@breif Player�̎���ł��邩�̎擾�B
	*/
	bool GetDead()
	{
		return m_isDead;
	}
	/*!
	 *@breif�@Player�̃��X�^�[�g���̏��擾�p�B
	*/
	bool GetReStart()
	{
		return m_reStart;
	}
	/*!
	 *@breif���񐔎擾
	*/
	int GetWeekBack()
	{
		return m_weekbackNum;
	}
	/*!
	 *@breif���X�^�[�g���̏��擾�I��
	*/
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
	/// <summary>
	/// �p�b�h�擾
	/// </summary>
	/// <param name="gamePad"></param>
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
	//�A�j���[�V����
	enum HumanAnimationClip {
		enAnimationClip_test,
		enAnimationClip_num
	};
	wchar_t m_name[256] ;								//�p�X�l�[��
	wchar_t m_specName[256];							//�X�y�L�����}�b�v�p�X
	AnimationClip m_animClip[enAnimationClip_num];		//�A�j���[�V�����N���b�v
	Animation m_animation;								//�A�j���[�V����
	SkinModel m_model;									//�X�L�����f���B
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[�i�R���W�����j
	std::vector<CoursePass*> m_courcePassList;			//�R�[�X�ʉߔ���p
	std::vector<CoursePass*> m_reStartPassList;			//���������㕜������|�W�V����
	std::vector<CPSwitchG*> m_cpGhostList;
	std::vector<WeekBackPass*> m_weekbackPassList;		//���񔻒�p
	std::vector<CoursePass*> m_deadZoneList;			//�������p
	std::vector<bool> m_weekBackOver;					//����ɒʉ߂������ǂ���
	std::vector<bool> m_reStartOver;					//����ɒʉ߂������ǂ���
	Effekseer::Effect* m_sampleEffect = nullptr;		//�G�t�F�N�g�p
	Effekseer::Handle m_playEffectHandle = -1;
	PlayerData* m_playerData		  = nullptr;		//�L�������̃p�����[�^
	GamePad* m_gamePad	              = nullptr;			
	GameData* m_gamedata			  = nullptr;
	CVector3 m_position		 = CVector3::Zero();		//�|�W�V����
	CVector3 m_moveSpeed	 = CVector3::Zero();		//�X�s�[�h
	CVector3 m_accel		 = CVector3::Zero();		//�����x
	CVector3 m_jump			 = CVector3::Zero();		//�W�����v�̉����x
	CVector3 m_reStartPos	 = CVector3::Zero();		//���X�^�[�g�|�W�V����
	CQuaternion m_reStartRot = CQuaternion::Identity(); //���X�^�[�g�̌���
	CQuaternion m_rot	     = CQuaternion::Identity(); //����
	CQuaternion m_effectRot  = {0.0f,0.0f,90.0f,1.0f};  //�G�t�F�N�g�̌���
	const float m_radius       = 30.0f;			//�����蔻��̔��a
	const float m_height       = 20.0f;			//�����蔻��̍���
	const float m_gravity	   = 100.0f;		//�d��
	const float m_frictionOver = 0.98f;			//���C�ő�
	const float m_frictionAdd  = 1.01f;			//�ɂ₩�Ȗ��C
	const float m_Addjump	   = 400.0f;		//�W�����v�͂ɏ�Z����l
	float m_friction	 = 0.98f;				//���C�x
	float m_movePower	 = 100.0f;				// �ړ����x
	float m_jumpPower	 = 0.0f;				//�W�����v��
	float m_cooltime     = 0.0f;				//�����N�[���^�C��
	int m_passNum		 = 0;					//�ʉ߂����p�X�̐�
	int m_weekbackNum	 = 0;					//����
	int m_charaNum		 = 0;					//�L�����ԍ�
	bool m_first		 = false;				//Update�ň�x�������s
	bool m_goal			 = false;				//�S�[���p
	bool m_one			 = false;				//��x�����ʂ��p
	bool m_isDead        = false;				//���ʒm�p
	bool m_reStart		 = false;				//���X�^�[�g�p
	bool m_isJump		 = false;				//�W�����v�p
	bool m_isTime		 = false;				//������
	
	//todo  �X�y�L�����}�b�v
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;
	//todo �@���}�b�v
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;

};


