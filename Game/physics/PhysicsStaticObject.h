/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include "PhysicsObjectBase.h"

/*!
* @brief	�ÓI�����I�u�W�F�N�g
*/
class PhysicsStaticObject : public PhysicsObjectBase{
public:
	~PhysicsStaticObject()
	{
		Release();
	}
	/*!
	* @brief	����B
	*/
	void Release() override final;
	/*!
	* @brief	���W�Ɖ�]��ݒ�B
	*/
	void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
	{
		m_rigidBody.SetPositionAndRotation(pos, rot);
	}
	RigidBody& GetRigidBody()
	{
		return m_rigidBody;
	}
	/*!
	* @brief	���b�V���̐ÓI�I�u�W�F�N�g���쐬�B
	*@param[in]	skinModel	�X�L�����f���B
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*/
	void CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot);
	//������
private:

	/*!
	* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot) override final;
private:
	RigidBody m_rigidBody;				//!<���́B
	MeshCollider m_meshCollider;
};
