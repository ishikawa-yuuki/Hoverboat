#pragma once
class GamePad
{
public:
	virtual bool		IsPressAccel()	= 0;
	virtual bool		IsPressJump()   = 0;
	virtual void		HitReStartPos() = 0;
	virtual void		isDead() =0 ;
	virtual void		HitGhost()		= 0;
	virtual void		HitCourcePass()	= 0;
	virtual void		NotHitPass()	= 0;
	virtual void		Move()		    = 0;
	virtual void        Rotation()		= 0;
	virtual float		GetLstickXF()   = 0;
	virtual CQuaternion GetRotation()   = 0;
	virtual CVector3	GetDirection()  = 0;
	
};