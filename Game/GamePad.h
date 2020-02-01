#pragma once
class GamePad
{
public:
	virtual bool		IsPressAccel()	= 0;
	virtual bool		IsPressJump()   = 0;
	virtual void		CheckGhost()	= 0;
	virtual void		Move()		    = 0;
	virtual void        Rotation()		= 0;
	virtual float		GetLstickXF()   = 0;
	virtual CQuaternion GetRotation()   = 0;
	virtual CVector3	GetDirection()  = 0;
	
};