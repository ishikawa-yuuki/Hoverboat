#pragma once
#include "GameObjectManager.h"
class Player;
class GameData;
class GameCamera : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameCamera();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameCamera();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Render() {};

	/// <summary>
	/// player���R�s�[
	/// </summary>
	void SetInfoPlayer(Player* pl)
	{
		m_player = pl;
	}
private:
	Player* m_player =nullptr;							//�v���C���[
	GameData* m_gamedata = nullptr;						//�Q�[���f�[�^
	CVector3 m_target = CVector3::Zero();				//�^�[�Q�b�g
	CVector3 m_position = CVector3::Zero();				//�|�W�V����
	CVector3 m_toCameraPos = { 0.0f, 0.0f, 400.0f };	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	CVector3 m_rePosition = CVector3::Zero();			//���X�^�[�g���̃|�W�V����
	CVector3 m_reTarget = CVector3::Zero();				//���X�^�[�g���̃^�[�Q�b�g
	CVector3 m_retoCameraPos = m_toCameraPos;			//���X�^�[�g���̃J����
	
};

