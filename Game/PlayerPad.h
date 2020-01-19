#pragma once
#include "character/CharacterController.h"
#include "PhysicsGhostObject.h"
#include "GamePad.h"
class CPSwitchG;
class PlayerPad : public GamePad
{
public:
	PlayerPad();
	~PlayerPad();
	bool Start();
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
	/// <summary>
	/// 周回判定処理
	/// </summary>
	void Check();

	void  UpdatePad();

	float PlayerPad::GetLstickXF()
	{
		return g_pad[0].GetLStickXF();
	}
	bool PlayerPad::IsPressAccel()
	{
		return g_pad->IsPress(enButtonRB1);
	}
	bool PlayerPad::IsPressJump()
	{
		return g_pad->IsPress(enButtonA);
	}
	CVector3 PlayerPad::GetPosition()
	{
		return m_position;
	}
	CQuaternion PlayerPad::GetRotation()
	{
		return m_rot;
	}
	const std::vector<CPSwitchG*>& GetGhostObjectList(const std::vector<CPSwitchG*>& List)
	{
		m_cpGhostList = List;
		return m_cpGhostList;
	}
private:
	CharacterController m_charaCon;
	std::vector<CPSwitchG*> m_cpGhostList;
	float m_movePower = 100.0f;// 移動速度
	float m_friction = 0.98f;   //摩擦度
	bool m_first = false;
	bool m_over = true;
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_accel = CVector3::Zero();	//加速度。
	CVector3 m_jump = CVector3::Zero();     //ジャンプの加速度
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_position = { 10.0f,20.0f,0.0f };
	CVector3 m_moveDirection = g_camera3D.GetForward();//移動時の奥方向
	CVector3 m_cameraForward = g_camera3D.GetForward();//カメラの前方方向を取得。
	
};