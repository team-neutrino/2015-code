#include "WPILib.h"
#include "Drive.h"
#include "Gyro.h"
#pragma once

class AutonomousDriver
{
public:
	AutonomousDriver(Drive* driveinst);
	void TurnDegrees(float degrees);
	void MoveDistance(float feet);
	void FeetMoved(float feetmoved);
private:

	Drive* DriveInst;
//	Gyro Gyroscope;
};
