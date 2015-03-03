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

	void SetLeft(double speed);

	void SetRight(double speed);

	void Stop();

	void Open(bool open);

private:
	Victor SuckyMotorLeft;
	Victor SuckyMotorRight;

	Solenoid SuckySolenoidOpen;
	Solenoid SuckySolenoidClose;
};
