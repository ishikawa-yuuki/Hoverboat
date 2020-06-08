#pragma once
/*!
 * @brief	�Q�[���f�[�^�N���X�B
 */
class GameData
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameData() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameData() {};
public:
	static GameData& GetInstance()
	{
		static GameData gamedata;
		return gamedata;
	}

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �|�[�Y�ݒ�
	/// </summary>
	void SetPose()
	{
		m_pose = true;
	}

	/// <summary>
	/// �|�[�Y�L�����Z��
	/// </summary>
	void SetCanselPose()
	{
		m_pose = false;
	}

	/// <summary>
	/// �|�[�Y���擾
	/// </summary>
	/// <returns></returns>
	bool GetPose()
	{
		return m_pose;
	}

	/// <summary>
	/// �S�[���ݒ�
	/// </summary>
	void SetGoal()
	{
		m_goal = true;
	}

	/// <summary>
	/// Player�̏�Ԃ�ݒ�
	/// </summary>
	/// <param name="state">true�Ȃ�PC,false�Ȃ�NPC</param>
	void SetPlayerState(bool state)
	{
		m_playerState = state;
	}

	/// <summary>
	/// �L�����I��ݒ�
	/// </summary>
	/// <param name="num">�L�����ԍ�</param>
	void SetCharaNum(int num)
	{
		m_CharaNum = num;
	}

	/// <summary>
	/// �L�����̔ԍ��擾
	/// </summary>
	/// <param name="charaNum">�L�����̍ő吔</param>
	/// <returns>�I���L�����ԍ�</returns>
	int GetCharaNum(int charaNum_MAX)
	{
		if (!m_playerState)
		{
			int charaRandam;
			charaRandam = rand() % charaNum_MAX;
			return charaRandam;
		}
		return m_CharaNum;
	}

	/// <summary>
	/// �S�[�����擾
	/// </summary>
	/// <returns></returns>
	bool GetGoal()
	{
		return m_goal;
	}

	/// <summary>
	/// ���ʂ��i�[����֐�
	/// </summary>
	/// <param name="minute">��</param>
	/// <param name="second">�b</param>
	/// <param name="comma">�R���}</param>
	/// <param name="PlayerNo">�L�����i���o�[</param>
	void List_push_buck(int minute, int second, float comma, int PlayerNo);

	/// <summary>
	/// �S�[�����̕��擾
	/// </summary>
	/// <param name="i">�L�����ԍ�</param>
	/// <returns></returns>
	int GetMinute(int i)
	{
		return m_rankingList[i].m_minute;
	}

	/// <summary>
	/// �S�[�����̕b�擾
	/// </summary>
	/// <param name="i">�L�����ԍ�</param>
	/// <returns></returns>
	int GetSeond(int i)
	{
		return m_rankingList[i].m_second;
	}

	/// <summary>
	/// �S�[�����̃R���}4�擾
	/// </summary>
	/// <param name="i">�L�����ԍ�</param>
	/// <returns></returns>
	float GetComma(int i)
	{
		return m_rankingList[i].m_comma;
	}

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="i">�L�����ԍ�</param>
	/// <returns></returns>
	int GetNum(int i)
	{
		return m_rankingList[i].PlayerNo;
	}

	/// <summary>
	/// ���X�g�T�C�Y�擾
	/// </summary>
	/// <returns></returns>
	int GetListSize()
	{
		return m_rankingList.size();
	}
	struct RankResult
	{
		int   m_minute = 0;		//��
		int	  m_second = 0;		//�b
		float m_comma  = 0.0f;	//�R���}
		int PlayerNo   = 0;		//�v���C���[�ԍ�

	};
private:
	std::vector<RankResult> m_rankingList;	//�����L���O���X�g
	bool m_goal		    = false;					//�S�[������
	bool m_pose			= false;					//�|�[�Y���
	bool m_playerState  = true;					    //NPC��PC��(true��PC)
	int m_CharaNum		= 0;						//�L�����ԍ�
};

