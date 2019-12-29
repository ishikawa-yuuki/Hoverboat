#include "stdafx.h"
#include "ComputerPad.h"


ComputerPad::ComputerPad()
{
}


ComputerPad::~ComputerPad()
{
}
void ComputerPad::UpdatePad()
{
	if (g_pad[0].IsPress(enButtonUp))
	{
		if (m_pressAccel) {
			m_pressAccel = false;
		}
		else {
			m_pressAccel = true;
		}
	}
}