#pragma once
#include "GameObjectManager.h"
/// <summary>
/// ���[�X�X�^�[�g�n�_�N���X
/// </summary>
class StartRacePos : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StartRacePos();
	/// <summary>
	///�@�f�X�g���N�^
	/// </summary>
	~StartRacePos();
	void Update() {};
	void Render() {};
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	const CVector3& GetPosition()const
	{
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero();
};

