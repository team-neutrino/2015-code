#include "WPILib.h"
#pragma once

class Drive
{
public:
	Drive();
	/**
	 * Sets the left motor speed.
	 */
	void SetLeft(float speed);

	/**
	 * Sets the right motor speed.
	 */
	void SetRight(float speed);

private:
	Victor MotorLeft1;
	Victor MotorLeft2;
	Victor MotorRight1;
	Victor MotorRight2;
};
