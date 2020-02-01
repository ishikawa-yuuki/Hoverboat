#pragma once
#include "GamePad.h"
class CoursePass;
class ComputerPad : public GamePad
{
public:
	ComputerPad();
	~ComputerPad();
	bool Start();
	/// <summary>
   /// ‰ñ“]ˆ—
   /// </summary>
	void Rotation();
	/// <summary>
	/// ˆÚ“®ˆ—
	/// </summary>
	void Move();
	/// <summary>
	/// ƒWƒƒƒ“ƒvˆ—
	/// </summary>
	void Jump();

	void CheckGhost();

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
	CQuaternion GetRotation()
	{
		return m_rot;
	}
	CVector3    GetDirection() { return m_cpDirection; }
	void SetPosition(CVector3 const& pos) { m_position = pos; }
	const std::vector<CoursePass*>& SetPassObjectList(const std::vector<CoursePass*>& List)
	{
		m_courcePassList = List;
		return m_courcePassList;
	}
private:
	std::vector<CoursePass*> m_courcePassList;
	bool m_pressAccel		   = true;
	bool m_pressJump		   = false;
	bool m_first			   = false;
	float m_stickL			   = 0.0f;
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_position		   = CVector3::Zero();
	CVector3 m_passDirection   = CVector3::Zero();//Pass‚Ì‰œ•ûŒü
	CVector3 m_cpDirection     = CVector3::Zero();//Computer‚Ì‰œ•ûŒü
	int		 i = 0;
};

