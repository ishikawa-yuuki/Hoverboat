#pragma once
#include "character/CharacterController.h"
#include "GamePad.h"
class CPSwitchG;
class Pass;
class ComputerPad : public GamePad
{
public:
	ComputerPad();
	~ComputerPad();
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

	void Check();
	float GetLstickXF()
	{
		return m_stickL;
	}
	bool  IsPressAccel()
	{
		return m_pressAccel;
	}
	bool  IsPressJump()
	{
		return m_pressJump;
	}
	CVector3	GetPosition() { return m_position; };
	CQuaternion GetRotation() { return m_rot; };
	void UpdatePad();
	const std::vector<CPSwitchG*>& GetGhostObjectList(const std::vector<CPSwitchG*>& List)
	{
		m_cpGhostList = List;
		return m_cpGhostList;
	}
	const std::vector<Pass*>& GetPassObjectList(const std::vector<Pass*>& List)
	{
		m_passList = List;
		return m_passList;
	}
private:
	std::vector<Pass*> m_passList;
	std::vector<CPSwitchG*> m_cpGhostList;
	CharacterController m_charaCon;
	bool m_pressAccel		   = false;
	bool m_pressJump		   = false;
	bool m_first			   = false;
	float m_stickL			   = 0.0f;
	float m_friction		   = 0.98f;   //摩擦度
	CQuaternion m_rot		   = CQuaternion::Identity();
	CVector3 m_position		   = { 10.0f,20.0f,0.0f };
	CVector3 m_accel		   = CVector3::Zero();	//加速度。
	CVector3 m_passDirection   = CVector3::Zero();//Passの奥方向
	CVector3 m_cpDirection    = CVector3::Zero();//Computerの奥方向
	CVector3 m_moveSpeed	   = CVector3::Zero();
	float	 m_movePower	   = 100.0f;// 移動速度
	int		 i = 0;
};

