#include "WPILib.h"
#pragma once

class Drive
{
public:
	Drive();
	void SetLeft(float speed);
	void SetRight(float speed);

private:
	Victor MotorLeft1;
	Victor MotorLeft2;
	Victor MotorRight1;
	Victor MotorRight2;
};
