#include "stdafx.h"
#include "PlayerPad.h"


PlayerPad::PlayerPad()
{
}


PlayerPad::~PlayerPad()
{
} 
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
