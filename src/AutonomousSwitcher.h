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
	AutonomousSwitcher(Drive* drive, Sucky* sucky, Lift* lift);
	void RunAuto();
	void ModeDriveForward();
	void ModeThreeToteStack();

private:
	DigitalSelectorSwitch Switch;
	std::thread DashboardThread;

	AutonomousDriver DriverInst;

	Sucky* SuckyInst;

	Lift* LiftInst;

	const double REFRESH_RATE = 5;

	void updateDashboardThread();
};
