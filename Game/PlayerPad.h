#pragma once
#include "GamePad.h"
class PlayerPad : public GamePad
{
public:
	PlayerPad();
	~PlayerPad();
	float GetLstickXF();
	bool  IsPressAccel();
	bool  IsPressJump();
	void  UpdatePad() {};
};

