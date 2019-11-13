#pragma once
#include "character/CharacterController.h"
class PlayerMove 
{
public:
	 bool Start();
	 void Update();
	 /// <summary>
	/// 回転処理
	/// </summary>
	 void Rotation();
	 /// <summary>
	 /// 移動処理
	 /// </summary>
	 void Move();
	 /// <summary>
	 /// ジャンプ処理
	 /// </summary>
	 void Jump();
	 /*!
	  *@brief	PlayerのPositionを取得。
	  */
	const CVector3& GetPlayerPosition()const
	{
		return m_position;
	}
	/*!
	 *@brief	PlayerのCQuaternionを取得。
	 */
	const CQuaternion& GetPlayerRotation()const
	{
		return m_rot;
	}
private:
	CharacterController m_charaCon;
	float m_movePower = 100.0f;// 移動速度
	float m_moveForceMultiplier = 2.0f; // 移動速度の入力に対する追従度
	float m_friction = 0.98f;   //摩擦度
	bool m_first = false;
	bool m_over = true;
	CVector3 m_accel = CVector3::Zero();	//加速度。
	CVector3 m_jump = CVector3::Zero();     //ジャンプの加速度
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_position = {10.0f,20.0f,0.0f};
	CVector3 m_moveDirection = g_camera3D.GetForward();//移動時の奥方向
	CVector3 m_cameraForward = g_camera3D.GetForward();//カメラの前方方向を取得。
	CQuaternion m_rot = CQuaternion::Identity();
};

