#include "WPILib.h"
#include "Drive.h"
#include "Gyro.h"
#include "Constants.h"
#pragma once

class AutonomousDriver
{
public:
	AutonomousDriver(Drive* driveinst);
	void TurnDegrees(float degrees);
	void MoveDistance(float feet, float spd = 1);
	void MoveForTime(float time);
private:

	Drive* DriveInst;
	Gyro Gyroscope;
	Encoder Encode;
};
