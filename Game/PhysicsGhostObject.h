#pragma once
#include "PhysicsObjectBase.h"
class PhysicsGhostObject : public PhysicsObjectBase
{
public:
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~PhysicsGhostObject() { Release(); };
	/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
	void Release() override final;
	/*!
		* @brief	�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������B
		*/
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	/*!
	* @brief ���W��ݒ�
	*/
	void SetPosition(const CVector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	/*!
	* @brief ��]��ݒ�
	*/
	void SetRotation(const CQuaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		rot.CopyTo(btRot);
		btTrans.setRotation(btRot);
	}
private:
	/*!
		* @brief	�S�[�X�g�쐬�����̋��ʏ����B
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot) override;
private:
	bool				m_isRegistPhysicsWorld = false; //!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject		m_ghostObject;//!<�S�[�X�g
};

