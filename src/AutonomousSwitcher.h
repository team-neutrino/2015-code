#include "WPILib.h"
#include "DigitalSelectorSwitch.h"
#include "Drive.h"
#include "AutonomousDriver.h"
#include "Sucky.h"
#include "Lift.h"
#include <thread>
#pragma once

class AutonomousSwitcher
{
public:
	AutonomousSwitcher(Drive* drive);
	void RunAuto();
	void ModeDriveForward();
	void ModeThreeToteStack();

private:
	Lift Lifter;
	Sucky Intake;
	DigitalSelectorSwitch Switch;
	std::thread DashboardThread;

	AutonomousDriver DriverInst;


	const double REFRESH_RATE = 5;

	void updateDashboardThread();
};
