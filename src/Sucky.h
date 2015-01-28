#include "WPILib.h"
#pragma once

class Sucky
{
public:
	Sucky();
	void SuckIn();
	void SpitOut();

private:
	Victor SuckyMotorLeft;
	Victor SuckyMotorRight;
};
