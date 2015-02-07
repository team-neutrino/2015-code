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

	void Stop();

private:
	Victor SuckyMotorLeft;
	Victor SuckyMotorRight;
};
