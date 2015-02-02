#include "WPILib.h"
#pragma once

class Sucky
{
public:
	Sucky();
	/**
	 * Sucks object into robot.
	 */
	void SuckIn();
	/**
	 * Ejects object out of robot.
	 */
	void SpitOut();

private:
	Victor SuckyMotorLeft;
	Victor SuckyMotorRight;
};
