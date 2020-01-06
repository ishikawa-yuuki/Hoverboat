#pragma once
class GamePad
{
public:
	virtual float		GetLstickXF()	= 0;
	virtual bool		IsPressAccel()	= 0;
	virtual bool		IsPressJump()	= 0;
	virtual void		UpdatePad()		= 0;
	virtual CVector3	GetPosition()	= 0;
	virtual CQuaternion GetRotation()	= 0;
};