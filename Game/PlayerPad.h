#pragma once
#include "GamePad.h"
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

	void PlayerPad::CheckGhost() {}
	bool PlayerPad::IsPressAccel()
	{
		return g_pad->IsPress(enButtonRB1);
	}
	bool PlayerPad::IsPressJump()
	{
		return g_pad->IsPress(enButtonA);
	}
	CQuaternion PlayerPad::GetRotation()
	{
		return m_rot;
	}
	CVector3 PlayerPad::GetDirection()
	{
		return m_moveDirection;
	}
	float PlayerPad::GetLstickXF()
	{
		return g_pad[0].GetLStickXF()* 1.4f;
	}
private:
	CVector3 m_moveDirection = g_camera3D.GetForward();//移動時の奥方向
	CVector3 m_cameraForward = g_camera3D.GetForward();//カメラの前方方向を取得。
	CQuaternion m_rot = CQuaternion::Identity();
	bool m_first = false;
};