#pragma once
class GamePad
{
public:

	virtual float GetLstickXF() =0;
	virtual bool  IsPress() = 0;
};

