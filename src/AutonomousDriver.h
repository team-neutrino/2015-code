#include "WPILib.h"
#pragma once

class AutonomousDriver
{
public:
	AutonomousDriver();
	void happenstance;
private:
	void TurnDegrees(float degrees);
	void MoveDistance(float feet);
	void FeetMoved(float feetmoved)
	Drive* Driver;
};
