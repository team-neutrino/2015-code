#include "WPILib.h"
#include "Drive.h"
#pragma once

class AutonomousDriver
{
public:
	AutonomousDriver();
private:
	void TurnDegrees(float degrees);
	void MoveDistance(float feet);
	void FeetMoved(float feetmoved);
	Drive* Driver;
};
